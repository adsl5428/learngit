@echo off&setlocal enabledelayedexpansion&
color 0A

echo.�����뱸ע
set /p remark=

git commit -m %remark%
git push
