@echo off&setlocal enabledelayedexpansion&
git pull
echo.git同步完成
ping -n 6 127.1 >nul