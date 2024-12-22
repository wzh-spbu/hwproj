@echo off
mkdir result_PGM

:: Generate Sierpinski Carpet
for /L %%d in (1,1,10) do (
    .\fractal.exe sierpinski_%%d.pgm sierpinski %%d
    echo Generated sierpinski_%%d.pgm
)

:: Generate Julia Set
for /L %%d in (1,1,10) do (
    .\fractal.exe julia_%%d.pgm julia %%d -0.7 0.27015
    echo Generated julia_%%d.pgm
)

echo All fractals generated successfully.
pause
