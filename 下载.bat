@echo off&setlocal enabledelayedexpansion&
git fetch --all
git reset --hard origin/master
echo.git同步完成
ping -n 6 127.1 >nul