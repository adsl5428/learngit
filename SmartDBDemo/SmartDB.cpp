// SmartDB.cpp : implementation file
//

#include "stdafx.h"
#include "SmartDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HINSTANCE hDLL;

typedef INT				(* SMARTDB_OPEN)			(const char *, sqlite3 **);
typedef UINT			(* SMARTDB_EXEC)			(sqlite3*, const char *, sqlite3_callback, void *, char **);
typedef UINT			(* SMARTDB_CLOSE)			(sqlite3 *);
typedef INT				(* SMARTDB_COLUMN_COUNT)	(sqlite3_stmt*);
typedef INT				(* SMARTDB_PREPARE)			(sqlite3*, const char*, int, sqlite3_stmt**, const char**);
typedef INT				(* SMARTDB_FINALIZE)		(sqlite3_stmt*);
typedef CONST CHAR *	(* SMARTDB_COLUMN_NAME)		(sqlite3_stmt*, int iCol);
typedef INT				(* SMARTDB_COLUMN_TYPE)		(sqlite3_stmt*, int iCol);
typedef INT				(* SMARTDB_STEP)			(sqlite3_stmt*);
typedef INT				(* SMARTDB_COLUMN_INT)		(sqlite3_stmt*, int iCol);
typedef CONST UCHAR *	(* SMARTDB_COLUMN_TEXT)		(sqlite3_stmt*, int iCol);
typedef CONST VOID *	(* SMARTDB_COLUMN_BLOB)		(sqlite3_stmt*, int iCol);
typedef DOUBLE			(* SMARTDB_COLUMN_DOUBLE)	(sqlite3_stmt*, int iCol);

SMARTDB_OPEN			SmartDBOpen;
SMARTDB_EXEC			SmartDBExecute;
SMARTDB_CLOSE			SmartDBClose;
SMARTDB_COLUMN_COUNT	SmartDBColumnCount;    // Function pointer
SMARTDB_PREPARE			SmartDBPrepare;
SMARTDB_FINALIZE		SmartDBFinalize;
SMARTDB_COLUMN_NAME		SmartDBColumnName;
SMARTDB_COLUMN_TYPE		SmartDBColumnType;
SMARTDB_STEP			SmartDBStep;
SMARTDB_COLUMN_INT		SmartDBColumnInt;
SMARTDB_COLUMN_TEXT		SmartDBColumnText;
SMARTDB_COLUMN_BLOB		SmartDBColumnBlob;
SMARTDB_COLUMN_DOUBLE	SmartDBColumnDouble;


/////////////////////////////////////////////////////////////////////////////
// SmartDB

// SmartDB constructor
CSmartDB::CSmartDB()
{
	InitInstance();
}

// Body of the distructor
CSmartDB::~CSmartDB()
{
	if (m_bLibLoaded)
	{
		FreeLibrary(hDLL);
		m_bLibLoaded = FALSE;
	}

	m_bConnected = FALSE;
}

// This is called every time a new object is created
// and set new object's initial values
BOOL CSmartDB::InitInstance()
{
	m_bConnected = FALSE;
	m_bLibLoaded = FALSE;

	m_bLibLoaded = InitLibrary();
	return TRUE;
}

// Try to load the exported functions of Sqlite DLL
// Called from InitInstance
BOOL CSmartDB::InitLibrary(void)
{
	BOOL bRetVal = FALSE;

	hDLL = LoadLibrary("sqlite3");
	if (hDLL)
	{
		SmartDBOpen = (SMARTDB_OPEN)GetProcAddress(hDLL, "sqlite3_open");
		SmartDBExecute = (SMARTDB_EXEC)GetProcAddress(hDLL, "sqlite3_exec");
		SmartDBClose = (SMARTDB_CLOSE)GetProcAddress(hDLL, "sqlite3_close");
		SmartDBColumnCount = (SMARTDB_COLUMN_COUNT)GetProcAddress(hDLL, "sqlite3_column_count");
		SmartDBPrepare = (SMARTDB_PREPARE)GetProcAddress(hDLL, "sqlite3_prepare");
		SmartDBFinalize = (SMARTDB_FINALIZE)GetProcAddress(hDLL, "sqlite3_finalize");
		SmartDBColumnName = (SMARTDB_COLUMN_NAME)GetProcAddress(hDLL, "sqlite3_column_name");
		SmartDBColumnType = (SMARTDB_COLUMN_TYPE)GetProcAddress(hDLL, "sqlite3_column_type");
		SmartDBStep = (SMARTDB_STEP)GetProcAddress(hDLL, "sqlite3_step");
		SmartDBColumnInt = (SMARTDB_COLUMN_INT)GetProcAddress(hDLL, "sqlite3_column_int");
		SmartDBColumnText = (SMARTDB_COLUMN_TEXT)GetProcAddress(hDLL, "sqlite3_column_text");
		SmartDBColumnBlob = (SMARTDB_COLUMN_BLOB)GetProcAddress(hDLL, "sqlite3_column_blob");
		SmartDBColumnDouble = (SMARTDB_COLUMN_DOUBLE)GetProcAddress(hDLL, "sqlite3_column_double");

		if (!SmartDBOpen || !SmartDBExecute
				|| !SmartDBClose		|| !SmartDBColumnCount
				|| !SmartDBPrepare		|| !SmartDBFinalize
				|| !SmartDBColumnName	|| !SmartDBColumnType
				|| !SmartDBStep			|| !SmartDBColumnInt
				|| !SmartDBColumnText	|| !SmartDBColumnBlob
				|| !SmartDBColumnDouble )
			m_bLibLoaded = FALSE;
		else
			m_bLibLoaded = TRUE;
	}
	if (m_bLibLoaded == FALSE)
		FreeLibrary (hDLL);

	return m_bLibLoaded;
}

/////////////////////////////////////////////////////////////////////////////
// SmartDB message handlers

// Try to Open the given database
// Returns TRUE on success
BOOL CSmartDB::Connect(LPCTSTR strDBPathName, LPCTSTR strParamString)
{
	if (m_bLibLoaded == FALSE)
		return FALSE;

	if (SmartDBOpen(strDBPathName, &db))	// If a non zero is returned, some problem occured
	{
		SmartDBClose(db);
		return FALSE;
	}

	m_bConnected = TRUE;
	return TRUE;
}

// Try to close the currently associated connection
BOOL CSmartDB::Close()
{
	SmartDBClose(db);
	m_bConnected = FALSE;
	return TRUE;
}

// Check if a connection is established or not
BOOL CSmartDB::IsConnected()
{
	return m_bConnected;
}

// Try to execute an SQL query
// Returns ZERO on success
UINT CSmartDB::Execute(LPCTSTR strQuery, UINT *nRecEfected)
{
	UINT nRetValue;
	char *zErrMsg = 0;
	if (SmartDBExecute (db, strQuery, NULL, 0, &zErrMsg) == SQLITE_OK)
		nRetValue = 0;
	else
	{
		nRetValue = 1;
	}
	return nRetValue;
}

// Return TRUE if Dynamic Link Library is loaded
// correctlly by Object Creation
BOOL CSmartDB::IsLibLoaded ()
{
	return m_bLibLoaded;
}

// SmartDBRecordSet.cpp : implementation file
//

/////////////////////////////////////////////////////////////////////////////
// CSmartDBRecordSet

// CSmartDBRecordSet constructor
CSmartDBRecordSet::CSmartDBRecordSet()
{
	InitInstance();
}

// Body of the distructor
CSmartDBRecordSet::~CSmartDBRecordSet()
{
	if (m_bIsOpen)
		Close();
}

// This is called every time a new object is created
// and set new object's initial values
BOOL CSmartDBRecordSet::InitInstance()
{
	m_bIsOpen = FALSE;
	m_nCurrentRecord = -1;
	m_nRecordCount = -1;
	m_nPageSize = 50;
	m_nPageCount = 0;
	m_nCurrentPage = 0;
	m_bIsProcessing = FALSE;
	m_nFieldsCount = 0;
	m_bIsOpen = FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSmartDBRecordSet message handlers

// Execute SQL Query for the established connection
// Mostly a SELECT query, Other queries may be executed using Execute()
// Returns TRUE on success
UINT CSmartDBRecordSet::Open(LPCTSTR strQueryString, CSmartDB *ptrConn, LONG nRSType)
{
	if (ptrConn->IsLibLoaded() == FALSE)
		return RSOPEN_NOLIBLOADED;

	if (m_bIsOpen)
		return RSOPEN_ALREADYOPENED;

	if (!ptrConn->IsConnected())
		return RSOPEN_NOCONNECT;
	
	CString strBuffer;			// Temp Buffer
	CStringArray *strRSRow;		// Record Set holder
	BOOL bTypesSaved = FALSE;	// Flag used to mark if DataTypes are saved for each column
	char *zErrMsg = 0;

	sqlite3_stmt *stmtByteCode;
	const char *strUnused = 0;
	UINT nCount = 0;
	UINT nRecCount = 0;
	INT nType;

	strBuffer = strQueryString;
	SmartDBPrepare(ptrConn->db, strBuffer, strBuffer.GetLength(), &stmtByteCode, &strUnused);

	nCount = SmartDBColumnCount(stmtByteCode);
	for (UINT i=0; i < nCount; i++)
	{
		strBuffer = SmartDBColumnName (stmtByteCode, i); // column_name
		strFieldsList.Add (strBuffer);
	}
	m_nFieldsCount = strFieldsList.GetSize();
	

	// return, If there is no field in the table
	if (m_nFieldsCount == 0)
		return RSOPEN_INVALIDQRY;

	m_bIsOpen = TRUE;

	int nValue;
	double nFValue;
	CString strValue;
	CString strTemp;

	while (SmartDBStep (stmtByteCode) != SQLITE_DONE)	// step
	{
		strRSRow = new CStringArray();

		for (i=0; (LONG)i < m_nFieldsCount; i++)
		{
			if (!bTypesSaved)	// Save Field Types in an array
			{
				nType = SmartDBColumnType (stmtByteCode, i);	// column_type
				nFieldsType.Add((UINT)nType);
				if ((LONG)i == m_nFieldsCount-1)
					bTypesSaved = TRUE;
			}
			
			switch (nFieldsType.GetAt(i))
			{
				case SQLITE_INTEGER:
					nValue = SmartDBColumnInt (stmtByteCode, i);
					strTemp.Format("%d", nValue);
					strRSRow->Add(strTemp);
					break;
				case SQLITE_FLOAT:
					nFValue = SmartDBColumnDouble (stmtByteCode, i);
					strTemp.Format("%f", nFValue);
					strRSRow->Add(strTemp);
					break;
				case SQLITE_TEXT:
					strValue = SmartDBColumnText (stmtByteCode, i);
					strRSRow->Add(strValue);
					break;
				case SQLITE_BLOB:
					strValue = (LPCTSTR)SmartDBColumnBlob (stmtByteCode, i);
					strRSRow->Add(strValue);
					break;
				case SQLITE_NULL:
					strRSRow->Add("");
					break;
			}
		}
		orsRows.Add((CObject *)strRSRow);
		nRecCount++;
	}

	m_nRecordCount = nRecCount;
	m_nCurrentRecord = 0;

	SmartDBFinalize(stmtByteCode);

	return RSOPEN_SUCCESS;
}

// Try to close the currently opened recordset
// Returns TRUE on success
BOOL CSmartDBRecordSet::Close()
{
	if (!m_bIsOpen)
		return FALSE;

	CStringArray *strRSRow;

	if (m_bIsOpen)
	{
		for (LONG i = m_nRecordCount-1; i >= 0; i--)
		{
			strRSRow = (CStringArray *)orsRows.GetAt(i);
			delete (strRSRow);
		}
		orsRows.RemoveAll();

		// Clear field list
		strFieldsList.RemoveAll();
		nFieldsType.RemoveAll();

		m_nFieldsCount = strFieldsList.GetSize();
		m_bIsOpen = FALSE;
		return TRUE;
	}
	else
		return FALSE;
}

// Returns number of rows in the current RecordSet
LONG CSmartDBRecordSet::RecordCount()
{
	if (m_bIsOpen)
		return m_nRecordCount;
	else
		return (-1L);
}

// Returns TRUE if record pointer has skipped the last record
BOOL CSmartDBRecordSet::IsEOF()
{
	if (!m_bIsOpen)
		return TRUE;

	return (m_nCurrentRecord == m_nRecordCount);
}

// Move the Record pointer to the very first row of the record set
void CSmartDBRecordSet::MoveFirst()
{
	ASSERT (m_bIsOpen);

	m_nCurrentRecord = 0;
	return;
}

// Move the Record pointer to the last row of the record set
void CSmartDBRecordSet::MoveLast()
{
	ASSERT (m_bIsOpen);

	m_nCurrentRecord = m_nRecordCount - 1;
	return;
}

// Move the Record pointer to the previous row
void CSmartDBRecordSet::MovePrevious()
{
	ASSERT (m_bIsOpen);

	if (m_nCurrentRecord > 0)
		m_nCurrentRecord--;
	return;
}

// Move the Record pointer to the previous row
void CSmartDBRecordSet::MoveNext()
{
	ASSERT (m_bIsOpen);

	if (m_nCurrentRecord < m_nRecordCount)
		m_nCurrentRecord++;
	return;
}

// Returns the Name of the Field (or Column) whose
// index is given
LPCTSTR CSmartDBRecordSet::GetFieldName(LONG nIndex)
{
	ASSERT (m_bIsOpen);

	if (nIndex < strFieldsList.GetSize())
		return strFieldsList.GetAt(nIndex);
	else
		return NULL;
}

// Returns the Type of the Field (or Column) whose
// index is given
INT CSmartDBRecordSet::GetFieldType(LONG nIndex)
{
	if (nIndex < nFieldsType.GetSize())
		return (INT)nFieldsType.GetAt(nIndex);
	else
		return 0;
}

// Returns the Total number of Columns in the record set
UINT CSmartDBRecordSet::FieldsCount()
{
	ASSERT (m_bIsOpen);

	return m_nFieldsCount;
}


// Returns the value of the column index in string format
// for current row in the record set
LPCTSTR CSmartDBRecordSet::GetColumnString(LONG nIndex)
{
	if (m_nCurrentRecord < 0 || m_nCurrentRecord >= m_nRecordCount || nIndex >= m_nFieldsCount)
		return NULL;

	CStringArray * strArr;
	strArr = (CStringArray *)orsRows.GetAt(m_nCurrentRecord);
	
	return strArr->GetAt(nIndex);
}
