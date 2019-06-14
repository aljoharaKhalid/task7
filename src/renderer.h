#ifndef _glrenderer_h_
#define _glrenderer_h_

#define CLEAR_COLOR_BIT 0x1
#define CLEAR_DEPTH_BIT 0x2

// Image represents texture and framebuffer image information
// It includes whatever is needed to bind it for rendering
struct ImageObj;
typedef struct ImageObj *Image;

// Buffer is a wrapper object for the API elements of a buffer object
struct BufferObj;
typedef struct BufferObj *Buffer;

// Uniform represents the uniform interface to the pipeline shaders
// Maximum allowable textures is 2.
struct UniformObj;
typedef struct UniformObj *Uniform;

// Pipeline represents the shader and fixed function states that make up the rendering pipeline
struct PipelineObj;
typedef struct PipelineObj *Pipeline;

// Initialize persistent global state for the renderer. returns 0 on success
int init_renderer();
// Clear the full framebuffer for the attachments indicated by the <bitfield>
void clear_frame(uint32_t bitfield);
// Clear the a portion of the  framebuffer indicated by <x,y,width,height>
// for the attachments indicated by the <bitfield>
void subclear_frame(uint32_t bitfield, int32_t x, int32_t y, int32_t width, int32_t height);
// set viewport for the framebuffer limited to <x,y,width,height>
void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height);
// Generate a buffer object of <size> bytes and initialize with <data> and return its handle
Buffer gen_buffer(int32_t size, float *data);
// Delete the buffer object represented by <buffer>
void del_buffer(Buffer buffer);
// Allocate and return memory for attribs consisting of <components> attribs for <faces> quads
float *malloc_faces(int components, int faces);
// Generate a vertex buffer representing <faces> quads with vertex attributes
// consisting of <components> attributes using <data>  and return its handle
Buffer gen_faces(int components, int faces, float *data);
// Draw lines consisting of <count> 2D or 3D vertices with <components> components
// taken from vertex buffer <buffer> at <width> pixels
void draw_lines(Buffer buffer, int components, int count, float width);
// Draw landscape chunk using vertex buffer <buffer> consisting of <faces> quads
void draw_chunk(Buffer buffer, int faces);
// Draw UI placement option represented by vertex buffer <buffer>
// consisting of <count> vertices
void draw_item(Buffer buffer, int count);
// Draw UI text represented by vertex buffer <buffer> of <length> characters
void draw_text(Buffer buffer, int length);
// Draw text placed on landscape chunks represented by vertex buffer <buffer>
// of <faces> characters
void draw_signs(Buffer buffer, int faces);
// Draw text currently being applied to a chunk represented by vertex buffer <buffer>
// of <length> characters
void draw_sign(Buffer buffer, int length);
// Draw UI landscape chunk placement option represented by vertex buffer <buffer>
void draw_cube(Buffer buffer);
// Draw UI plant placement option represented by vertex buffer <buffer>
void draw_plant(Buffer buffer);
// Draw player cube represented by vertex buffer <buffer>
void draw_player(Buffer buffer);
// Draw large sphere around origin represented by vertex buffer <buffer>
void draw_sky(Buffer buffer);
// Create a uniform interface object containing a ubo of size <ubo_size>
// and textures <texture0> and <texture1> then return the handle.
Uniform gen_uniform(uint32_t ubo_size, Image texture0, Image texture1);
// Destroy <uniform> and free any associated memory.
void del_uniform(Uniform uniform);
// Load and create a texture image from the file located in <path>
// filter and clamp according to <linear> and <clamp> and return the created image object
Image load_tex_image(const char *path, int linear, int clamp);
// Destroy <image> and free any associated resources
void del_image(Image image);
// Create pipeline object containing shaders as extracted from files <path1> and <path2>
Pipeline gen_pipeline(const char *path1, const char *path2);
// Bind the pipeline and <uniform> interfaces for rendering
// and init ubo with <size> bytes of <data>
void bind_pipeline(Pipeline pipeline, Uniform uniform, int size, void *data);
// Destroy pipeline object <pipeline> and free any associated memory
void del_pipeline(Pipeline pipeline);

#endif // _glrenderer_