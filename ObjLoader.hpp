/*
 * Made by Ruben Ballet (ruben.ballet@gmail.com)
 *
 * Simple modelloader for .obj files.
 * I made this object loader cause most objectloaders load vertices multiple times.
 * This object loader loads every vertices once and references to them with indices.
 * If you want to load an object for rendering you better use another loader (eg. Assimp).
 * This loader is for loading the minimum amount of vertices, if you want to do calculations with the vertices.
 *
 * More options for loading are coming in the future.
 * Check the readme for more information.
 *
 * Feel free to use this objectloader.
 * If you modify this file and redistribute it, please mention my name.
 */

#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>


/**
 * Simple modelloader for .obj files.
 * This loader only loads vertices, indices and normals.
 * The option to also load texture coordinates will be added in the future.
 * Models are loaded from a file, by calling the "LoadFromFile" method.
 * You can get the vertices, indices and normals by calling the related getmethod.
 */
class ObjLoader {

public:
	ObjLoader() {
		m_errorString = "No Error";
		Error = false;
		m_vertices = new std::vector<float>();
		m_normals = new std::vector<float>();
		m_indices = new std::vector<unsigned int>();
	}

	~ObjLoader() {
		delete m_vertices;
		delete m_normals;
		delete m_indices;
	}

	/**
	 * @brief Loads model from file
	 * @param const std::string& file - obj file you want to load
	 * @return bool - true if loading is successful, false if loading failse
	 *		When loading failes an error message can be retrieved with the "GetErrorString" method.
	 */
	bool LoadFromFile(const std::string& file) {
		Clear();
		std::string line;
		std::ifstream infile(file);
		if (infile.fail()) {
			m_errorString = "Failed to open file" + file;
			Error = true;
			return false;
		}
		int lineNumber = 0;
		while (std::getline(infile, line))
		{
			std::stringstream ss(line);
			std::string firstChar;
			ss >> firstChar;
			if (firstChar.compare("#") == 0) {
				if (!ProcessComment(line)) {
					Error = true;
					m_errorString = "Parse error on line: " + lineNumber;
					return false;
				}
			}
			else if (firstChar.compare("v") == 0) {
				if (!ProcessV(ss)) {
					Error = true;
					m_errorString = "Parse error on line: " + lineNumber;
					return false;
				}
			}
			else if (firstChar.compare("vt") == 0) {
				if (!ProcessVT(ss)) {
					Error = true;
					m_errorString = "Parse error on line: " + lineNumber;
					return false;
				}
			}
			else if (firstChar.compare("vn") == 0) {
				if (!ProcessVN(ss)) {
					Error = true;
					m_errorString = "Parse error on line: " + lineNumber;
					return false;
				}
			}
			else if (firstChar.compare("f") == 0) {
				if (!ProcessF(ss)) {
					Error = true;
					m_errorString = "Parse error on line: " + lineNumber;
					return false;
				}
			}
			else {

			}
			++lineNumber;
		}
		return true;
	}

	/**
	 * @brief Clears the model data
	 */
	void Clear() {
		if (m_vertices)
			m_vertices->clear();
		if (m_indices)
			m_indices->clear();
		if (m_normals)
			m_normals->clear();
	}

	/**
	 * @brief returns copy of the vector of vertices
	 */
	std::vector<float> GetVertices() {
		return *m_vertices;
	}

	/**
	 * @brief returns copy of the vector of normals
	 */
	std::vector<float> GetNormals() {
		return *m_normals;
	}

	/**
	 * @brief returns copy of the vector of indices
	 */
	std::vector<unsigned int> GetIndices() {
		return *m_indices;
	}

	/**
	 * @brief returns error string
	 */
	std::string GetErrorString() { return m_errorString; }

	/**
	 * @brief Is false if an error occurred
	 */
	bool Error;

private:
	bool ProcessComment(const std::string& line) {
		//Do nothing
		return true;
	}
	bool ProcessV(std::stringstream& ss) {
		double x, y, z;
		if(!(ss >> x >> y >> z))
			return false;
		m_vertices->push_back(x);
		m_vertices->push_back(y);
		m_vertices->push_back(z);
		return true;
	}
	bool ProcessF(std::stringstream& ss) {
		std::string x, y, z;
		if (!(ss >> x >> y >> z))
			return false;
		ProcessIndex(x);
		ProcessIndex(y);
		ProcessIndex(z);
		return true;
	}
	bool ProcessIndex(const std::string& s) {
		std::stringstream ss(s);
		std::string result;
		std::vector<std::string> strings;
		while (std::getline(ss, result, '/')) {
			strings.push_back(result-1);
		}
		if (strings.size() >= 1)
			m_indices->push_back(std::stoi(strings[0]));
		else if (strings.size() <= 0)
			return false;
		return true;
	}
	bool ProcessVT(std::stringstream& ss) {
		return true;
	}
	bool ProcessVN(std::stringstream& ss) {
		double x, y, z;
		if (!(ss >> x >> y >> z))
			return false;
		m_normals->push_back(x);
		m_normals->push_back(y);
		m_normals->push_back(z);
		return true;
	}

	std::string m_errorString;
	std::vector<float>* m_vertices = nullptr;
	std::vector<unsigned int>* m_indices = nullptr;
	std::vector<float>* m_normals = nullptr;

};

#endif //OBJ_LOADER_HPP