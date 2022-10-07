CXX = g++
DEBUGFLAGS = -g -DDXDEBUG
RELEASEFLAGS = -O3 -DNDEBUG

ifeq ($(OS), Windows_NT)
	SHELL = CMD
	CFLAGS = -c -Wall -std=c++2b -ftree-vectorize -mavx
	INCLUDE_DIR = 
	LDFLAGS = 
	EXE_OpenGLTestd = ./Debug/OpenGLTest.exe
	EXE_OpenGLTest = ./Release/OpenGLTest.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
		CFLAGS = -c -Wall -std=c++2b -ftree-vectorize -mavx
		INCLUDE_DIR = -I./Source/glad/include -I/usr/include/opencv4/
#		LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lopencv_imgcodecs -lopencv_core -lassimp
		LDFLAGS = -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl -lopencv_imgcodecs -lopencv_core -lassimp
#		-lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib
#		-lopencv_dnn -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg
#		-lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking
#		-lopencv_datasets -lopencv_text -lopencv_face -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc
#		-lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto
#		-lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core
		EXE_OpenGLTestd = ./Debug/OpenGLTest
		EXE_OpenGLTest = ./Release/OpenGLTest
    endif
endif

$(info init..)

opengltestd: ./Source/main.cpp $(EXE_OpenGLTestd)
opengltest: ./Source/main.cpp $(EXE_OpenGLTest)

./Debug/fly_like_camera.o: ./Source/fly_like_camera.cpp ./Source/fly_like_camera.hpp ./Source/err_def.hpp
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/model.o: ./Source/model.cpp ./Source/model.hpp				\
		./Source/err_def.hpp ./Source/glad/include/glad/glad.h		\
		./Debug/mesh.o
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/mesh.o: ./Source/mesh.cpp ./Source/mesh.hpp					\
		./Source/err_def.hpp ./Source/glad/include/glad/glad.h		\
		./Debug/shader.o											\
		./Debug/tx.o												\
		./Debug/buf.o												\
		./Debug/va.o
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/va.o: ./Source/va.cpp ./Source/va.hpp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/tx.o: ./Source/tx.cpp ./Source/tx.hpp ./Source/tx.ipp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/buf.o: ./Source/buf.cpp ./Source/buf.hpp ./Source/buf.ipp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/shader.o: ./Source/shader.cpp ./Source/shader.hpp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/glad.o: ./Source/glad/src/glad.c ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/window.o: ./Source/window.cpp ./Source/window.hpp ./Source/window.ipp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Debug/main.o: ./Source/main.cpp																		\
		./Source/err_def.hpp ./Source/glad/include/glad/glad.h											\
		./Debug/shader.o	./Debug/buf.o ./Debug/tx.o ./Debug/va.o ./Debug/model.o						\
		./Debug/window.o ./Debug/fly_like_camera.o
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(DEBUGFLAGS) $< -o $@

./Release/fly_like_camera.o: ./Source/fly_like_camera.cpp ./Source/fly_like_camera.hpp ./Source/err_def.hpp
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/model.o: ./Source/model.cpp ./Source/model.hpp				\
		./Source/err_def.hpp ./Source/glad/include/glad/glad.h		\
		./Release/mesh.o
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/mesh.o: ./Source/mesh.cpp ./Source/mesh.hpp				\
		./Source/err_def.hpp ./Source/glad/include/glad/glad.h		\
		./Release/shader.o											\
		./Release/tx.o												\
		./Release/buf.o												\
		./Release/va.o
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/va.o: ./Source/va.cpp ./Source/va.hpp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/tx.o: ./Source/tx.cpp ./Source/tx.hpp ./Source/tx.ipp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/buf.o: ./Source/buf.cpp ./Source/buf.hpp ./Source/buf.ipp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/shader.o: ./Source/shader.cpp ./Source/shader.hpp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/glad.o: ./Source/glad/src/glad.c ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/window.o: ./Source/window.cpp ./Source/window.hpp ./Source/window.ipp ./Source/err_def.hpp ./Source/glad/include/glad/glad.h
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

./Release/main.o: ./Source/main.cpp																		\
		./Source/err_def.hpp ./Source/glad/include/glad/glad.h											\
		./Release/shader.o ./Release/buf.o ./Release/tx.o ./Release/va.o ./Release/model.o				\
		./Release/window.o ./Release/fly_like_camera.o
	$(info processing....)
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(RELEASEFLAGS) $< -o $@

$(EXE_OpenGLTestd): ./Debug/main.o ./Debug/glad.o ./Debug/shader.o ./Debug/buf.o ./Debug/tx.o			\
		./Debug/va.o ./Debug/mesh.o ./Debug/model.o ./Debug/window.o ./Debug/fly_like_camera.o
	$(info processing......)
	$(CXX) $(LDFLAGS) $^ -o $@

$(EXE_OpenGLTest): ./Release/main.o ./Release/glad.o ./Release/shader.o ./Release/buf.o ./Release/tx.o	\
		./Release/va.o ./Release/mesh.o ./Debug/model.o ./Release/window.o ./Release/fly_like_camera.o
	$(info processing......)
	$(CXX) $(LDFLAGS) $^ -o $@

.PHONY: clean clean_bin clean_full
clean:
	rm -f ./Debug/*.o
	rm -f ./Release/*.o
clean_bin:
	rm -f $(EXE_OpenGLTestd)
	rm -f $(EXE_OpenGLTest)
clean_full:
	rm -f ./Debug/*.o
	rm -f ./Release/*.o
	rm -f $(EXE_OpenGLTestd)
	rm -f $(EXE_OpenGLTest)
#ifeq ($(OS), Windows_NT)
#	copy .\_TEST_\*.o .\*.o
#	del .\_TEST_\*.o
#else
#    UNAME_S := $(shell uname -s)
#    ifeq ($(UNAME_S), Linux)
#		rm *.o
#    endif
#endif