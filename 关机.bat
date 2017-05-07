@echo off&setlocal enabledelayedexpansion&
color 0A
git add .
echo.ÇëÊäÈë±¸×¢
set /p remark=

git commit -m "%remark%"
git push
pause