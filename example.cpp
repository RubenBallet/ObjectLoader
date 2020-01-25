#include <iostream>
#include "ObjLoader.hpp"

#ifndef TESTING

int main(int argc, char* argv[]) {
	ObjLoader loader;
	loader.LoadFromFile("Cube.obj");
	std::cout << loader.GetErrorString() << std::endl;
	
	if (loader.Error)
		return -1;
	
	std::vector<float> vertices = loader.GetVertices();
	std::vector<float> normals = loader.GetNormals();
	std::vector<unsigned int> indices = loader.GetIndices();
	loader.Clear();
	std::cout << "Vertices: ";
	for (int i = 0; i < vertices.size(); ++i) {
		std::cout << vertices[i] << " ";
	}
	std::cout << std::endl;

	std::cin.get();
	return 0;
}
#endif // !TESTING