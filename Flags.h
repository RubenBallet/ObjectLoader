#ifndef OBJLOADER_FLAGS
#define OBJLOADER_FLAGS

/*
 *Flags:
 *  - MIN_TRIANGLES -> minimum amount of triangles (otherwise every triangle is loaded twice times
 *  - GENERATE_NORMALS -> generate normals when no normals are given
 *  - GENERATE_NORMALS_FORCED -> generate normals even when normals are given
 *  - VERTICES_ONLY -> Load vertices withour indices
 */

/*
 * Generates every point and every triangle once
 * Normaly triangles are loaded twice, once for every side to make sure you can't see through the object
 */
#define MIN_TRIANGLES 0x1

/*
 * Generates normals when they are not given
 * NOT IMPLEMENTED!
 */
#define GENERATE_NORMALS 0x2
/*
 * Generates normals even when they are given
 * NOT IMPLEMENTED!
 */
#define GENERATE_NORMALS_FORCED 0x4

/*
 * Generate only vertices without indices
 * NOT IMPLEMENTED!
 */
#define VERTICES_ONLY 0x8


#endif
