mkdir -p build
cd build
cmake .. \
	-G "Visual Studio 14 2015 Win64" \
	-DOpenCV_DIR:PATH="C:/opencv-3.3.1/build"