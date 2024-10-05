# Quaternion Camera Demo
### Student Version 3

This demo is intended to teach you some of the calculations behind camera motion and quaternions. 
You will also better learn how to add nodes/instances to the scene through creating a racetrack with beacons, enemies and powerups. 

### Included:
- (D) demo - contains the binaries and scene
    - demo/project.godot - contains the project settings (eg. input mapping; main scene file)
    - demo/quat.tscn - main scene file
    - demo/bin/quat.gdextension - dictates the entry function (from register_types.cpp) and has the library locations for different systems
- (D) godot-cpp - contains the GDExtension API
    - Note: this MUST be the same version as the Godot binaries (editor) that you are using. 
- (D) resources - contains things that are displayed or referenced in the README.md document
- (D) src - contains all custom C++ classes (and their obj files) (student version differs)
    - example_abstract_class(.h/.cpp) - class to show how to create an abstract class
    - example_derived_class(.h/.cpp) - class to show how to derive from an abstract class
    - custom_scene_3501(.h/.cpp) - container class which will control the scene and handle collision detection etc. 
    - quat_camera(.h/.cpp) - the camera class which students will need to finish / fix
    - register_types(.h/.cpp) - exposes the C++ classes we create in GDExtension to the editor
    - defs.h - contains some useful constants

- .gitattributes - nothing of great value
- .gitmodules - links the godot-cpp directory to the official repository so that you can easily update it to a different version (if desired) using the command line
- .gitignore - ignores the binaries, .godot folder and sconsign.dblite (a temporary database used by SCons)
- SConstruct - similar to a Makefile, but for SCons to use. 
    - Note: This is only modified when creating a new demo with a different name. 
- README.md - the imagined assignment I wrote to go along with / structure the demo. Can be modified or scrapped as desired. 
- This INFO.md file

### Starting State
- This demo starts with the following node structure for the student version:
```
Node3D
├─ WorldEnvironment
├─ CustomScene3501
│  ├─ QuatCamera
│  ├─ Reference Points Group
│  │  ├─ Object_0
│  │  ├─ ...
│  │  ├─ Object_MAX
```
For the student version, you should see a field of boxes upon first startup. The scene will also have the broken camera. 

![Screenshot of the editor at start-up](resources/starting_state_student.png)

For the solution version, you will see an example racetrack with a camera. I did the racetrack in a circle. The starting beacon is the blue one. Students are encouraged to make their own creative choices with regards to beacon colors and track layout. 

```
Node3D
├─ WorldEnvironment
├─ CustomScene3501
│  ├─ QuatCamera
│  ├─ Beacons
│  │  ├─ Beacon0
│  │  ├─ ...
│  │  ├─ Beacon9
│  ├─ Enemies
│  │  ├─ Enemy0
│  │  ├─ ...
│  │  ├─ Enemy9
│  ├─ Powerups
│  │  ├─ Powerup0
│  │  ├─ ...
│  │  ├─ Powerup39
```

![Screenshot of the editor at start-up](resources/starting_state_solution.png)

### Additional Context
- The camera stores our_quaternion so that we can start from no rotation, and sets the internal axes to whatever the transformed camera node has. The quaternion that is stored in the Node3D class is the one we are setting by using the setup provided.  

### Dependencies
Includes (but not limited to)
```
<godot_cpp/classes/node3d.hpp>              - grandparent class of CranePart
<godot_cpp/classes/mesh_instance3d.hpp>     - parent class of CranePart
<godot_cpp/classes/camera3d.hpp>            - parent class of QuatCamera

<godot_cpp/classes/mesh.hpp>                
<godot_cpp/classes/array_mesh.hpp>       
<godot_cpp/classes/standard_material3d.hpp>
<godot_cpp/classes/shader_material3d.hpp>
<godot_cpp/classes/sprite2d.hpp> 
<godot_cpp/variant/vector3.hpp> 
<godot_cpp/variant/color.hpp> 
<godot_cpp/variant/vector2.hpp> 

// for building the ArrayMesh
<godot_cpp/variant/array.hpp>
<godot_cpp/variant/packed_vector3_array.hpp> 
<godot_cpp/variant/packed_vector2_array.hpp> 
<godot_cpp/variant/packed_color_array.hpp> 
<godot_cpp/variant/packed_int32_array.hpp>

<godot_cpp/classes/engine.hpp>              - used to skip some behaviour in the editor

<godot_cpp/variant/quaternion.hpp>
<godot_cpp/variant/vector3.hpp>
<godot_cpp/variant/transform3d.hpp>

<godot_cpp/variant/utility_functions.hpp>   - used for debug print statements

<godot_cpp/core/class_db.hpp>               - used by register_types to register classes
<godot_cpp/core/defs.hpp>
<godot_cpp/godot.hpp>
<gdextension_interface.h>
```
Software
```
Godot - v4.2.2.stable.official [15073afe3]
SCons CLI
```
### Watch Out For
- somehow not using quaternions for the camera; make sure students are not using anything else to move it. 

### Change Log
#### Pre-release
V1 - brought in create_and_add_as_child from lessons learned, fixed the camera problems
V2 - learned things from the first assignment, and cleaned up the code a tiny bit with that in mind. 
V3 - fixed problem based on the plane diagram. Thankfully before the release. 
#### Post-release

### Attribution
- Created by Samantha Beilman for COMP 3501