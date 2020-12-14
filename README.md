# Render Polygonal Meshes with OpenGL Fixed PipeLine

In this project, Implementing following function with OpenGL Fixed Pipeline

• Read and display arbitrary geometric models represented as triangle meshes interactivaly.There are two models on obj files folder.
• Translate the virtual camera along its own axes (not the axes in the world coordinate system)
• Rotate the virtual camera along its own axes
• Adapt camera with respect to the dimension of the 3D models
• Reset the camera to its original position.
• Support for rendering objects whose polygon vertices were defined using CW (clockwise) and CCW (counter-clockwise) orientation -- this will affect the behavior of the backface culling procedure
• Support for changing the values of the near and far clipping planes
• Support for the interactive change of colors (R, G, B) for the models, making sure that the color change is apparent under all rendering modes (lighting is not needed for this assignment) 
• Support for rendering the object using different kinds of primitives, such as points, wireframe and solid polygons (1 point);
• Support for reading a new model file through the user interface
