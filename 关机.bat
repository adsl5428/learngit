@echo off&setlocal enabledelayedexpansion&
color 0A

echo.ÇëÊäÈë±¸×¢
set /p remark=

git commit -m %remark%
git push
