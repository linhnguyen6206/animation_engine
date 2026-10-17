set(SRC
    transform.cpp
    bvhreader.cpp
    bvhwriter.cpp
    skeleton.cpp
    spline.cpp
    spline-basecode.cpp
    joint.cpp
    pose.cpp
    motion.cpp
    )

add_library(atk STATIC ${SRC})