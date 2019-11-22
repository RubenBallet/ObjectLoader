# ObjectLoader
Made by Ruben Ballet (ruben.ballet@gmail.com)

Simple modelloader for .obj files.
I made this object loader cause most objectloaders load vertices multiple times.
This object loader loads every vertices once and references to them with indices.
If you want to load an object for rendering you better use another loader (eg. Assimp).
This loader is for loading the minimum amount of vertices, if you want to do calculations with the vertices.

More options for loading are coming in the future.
Check the readme for more information.

Feel free to use this objectloader.
If you modify this file and redistribute it, please mention my name.

## Planned features

- [ ] Option for loading every triangle not more than once
- [ ] Loading texture coordinates
- [ ] Option for generating normals when they are not provided in the model
- [ ] Option for loading vertices without loading indices
