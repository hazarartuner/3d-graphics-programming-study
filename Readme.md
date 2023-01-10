# 3D Graphics Programming Study

This is my studying repository about 3D Computer Graphics Programming.

---

## My Progress

### 1. Draw Grid and Filled Cube
<p>
In this step, I learned the basics of how to draw pixel to the screen by using SDL2 library. I understand what the pixel/color buffer is.
</p>

![Alt text](src/images/progress/progress-1.png)
<br />
---
### 2. Point Cloud Cube with Orthographic Projection
<p>
In this step, I learned what the orthographic projection is and how to draw a 3D point cloud cube. With an extra effort I implemented basic transform animation :)
</p>

[![Alt text](src/images/progress/progress-2.png)](https://www.youtube.com/watch?v=Ty153Xvd2vg)
<br />
---

### 3. Point Cloud Cube with Perspective Projection
<p>
In this step, I learned what the perspective projection is and implemented it to the previously created point cloud cube.
</p>

[![Alt text](src/images/progress/progress-3.png)](https://www.youtube.com/watch?v=3LsBvYyZECQ)
<br />
---

### 4. Rotating Points in 3D Space
<p>
In this step, I learned how to rotate a point by using the basic trigonometry formulas. Then I rotate the entire mesh with an animation.
</p>

[![Alt text](src/images/progress/progress-4.png)](https://www.youtube.com/watch?v=SyssFz98J_Q)
<br />
---

### 5. Triangulated Wireframe Box
<p>
In this step, I learned how to draw a line between two points. Then, I refactored my box mesh code to re-structure it as a triangulated mesh. After that, I rendered the triangulated mesh by using the new draw line method that I learned.
</p>

[![Alt text](src/images/progress/progress-5.png)](https://www.youtube.com/watch?v=4Nr7DKie7uM)
<br />
---

### 6. Loading .OBJ Files
<p>
In this step, I learned how to read and parse .OBJ files. Then, I loaded a F22 aircraft model from a file. Before I watch the Gustavo's solution, I tried by myself and struggled while parsing a string in C. I tried to use regex for all steps but it was hard even I am good at regex. Then I watched the Gustavo's solution and it was much easier and simple and not require to use regexp for all steps :D The regex functions in C is not easy to use for non-familiar developers :)
</p>

[![Alt text](src/images/progress/progress-6.png)](https://www.youtube.com/watch?v=6YRxP8DEHtc)
<br />
---

### 7. Backface Culling
<p>
In this step, I learned how to implement back-face culling. It was much easier than I expected. We used two important Math concepts, the Dot Product and the Cross Product. I knew these math concepts before but using them in this implementation was eye opening. I think learning this technique will also help me in game development.
</p>

[![Alt text](src/images/progress/progress-7.png)](https://www.youtube.com/watch?v=pMPGMhtc3T0)
<br />
---


### 8. Triangle Rasterization
<p>
In this step, I learned how to fill a triangle, other means, "rasterization". We used flat-top and flat-bottom technique. I was always curious about filling triangles and it was like a magic thing in my mind until now :D Of course it is not so easy task but it is also not a magic :D</p>

[![Alt text](src/images/progress/progress-8.png)](https://www.youtube.com/watch?v=mQw__o2aTnU)
<br />
---

## About the Course

I study 3D Computer Graphics Programming with this wonderful course: https://pikuma.com/courses/learn-3d-computer-graphics-programming

Gustavo Pezzi teaches 3D graphics programming from scratch without using any 3d graphics library like OpenGL or DirectX. It is truly eye-opening and I recommend it whoever curious about how the computer graphics actually made.

---
### Packages that I used in this project

- Dynamic Array: https://github.com/gustavopezzi/dynamicarray