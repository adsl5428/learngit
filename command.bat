@echo off&setlocal enabledelayedexpansion&title Copy file folder to local
color 0A

echo.�����뱸ע
set /p remark=

git commit -m %remark=%
git push
pause