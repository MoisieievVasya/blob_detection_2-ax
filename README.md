# Project Overview

## blod_detection_2_ax

This project is designed to detect blobs in a video feed and adjust the drone's velocity to center the detected blob using a 2-axis control system. The project is divided into several modules:

- **videoProc**: Handles video processing and blob detection.
- **controls**: Contains the logic for adjusting the drone's velocity based on the detected blob's position.
- **communication**: Manages communication with the drone using MAVLink commands.
  
```sh
For better performance, it is recommended to use higher quality videos without green boxes.
```

# Build Instructions

## Dependencies

- CMake 3.30 or higher
- OpenCV 4.11.0
- MAVLink library

## Compilation Steps

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/blob_detection_2_ax.git
   cd blob_detection_2_ax
   ```

2. Create a build directory and navigate to it:
   ```sh
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```sh
   cmake ..
   ```

4. Build the project:
   ```sh
   make
   ```

## Note

In the `main.cpp` file, there is an absolute path to the video file that needs to be changed to the correct path on your system:
```cpp
std::string videoPath = "/Users/admin/Documents/GitHub/blod_detection_2-ax/videos/test_video2.mp4";
```
Make sure to update this path to point to the correct location of your video file.

# 2-Axis Control Logic

# 2-Axis Control Logic

The 2-axis control logic is designed to adjust the drone's velocity to center a detected blob in the video frame. This involves several steps, from detecting the blob to sending velocity commands to the drone. Here is a detailed explanation of each step:

## Blob Detection

The `videoProc` module processes each video frame to detect blobs using OpenCV's `SimpleBlobDetector`. The steps involved in blob detection are:

1. **Gaussian Blur**: Apply a Gaussian blur to the frame to reduce noise.
2. **Grayscale Conversion**: Convert the blurred frame to grayscale.
3. **Laplacian of Gaussian (LoG) Filter**: Apply the LoG filter to enhance edges.
4. **Thresholding**: Apply thresholding to the LoG output to enhance the edges further.
5. **Blob Detection**: Use OpenCV's `SimpleBlobDetector` to detect blobs in the thresholded image.
6. **Largest Blob Selection**: Select the largest blob from the detected blobs.

## Coordinate Calculation

Once the largest blob is detected, its coordinates are calculated relative to the center of the frame:

1. **Centroid Calculation**: Calculate the centroid of the largest blob.
2. **Image Center Calculation**: Calculate the center of the image.
3. **Offset Calculation**: Calculate the horizontal and vertical offsets of the blob's centroid from the image center.

## Velocity Adjustment

The `controls` module adjusts the drone's velocity based on the blob's position. The steps involved are:

1. **Offset Scaling**: Scale the horizontal and vertical offsets to calculate the velocity vector.
2. **Velocity Calculation**: Calculate the velocity vector components (`vx` and `vy`) based on the scaled offsets.
3. **MAVLink Command**: Send the calculated velocity commands to the drone using MAVLink.

## MAVLink Command

The `communication` module sends the calculated velocity commands to the drone using MAVLink. The steps involved are:

1. **Message Preparation**: Prepare the MAVLink message with the target position and velocity.
2. **Message Encoding**: Encode the MAVLink message.
3. **Message Sending**: Send the MAVLink message to the drone.


# Future Directions

## Waypoints Integration

### Overview
Integrating waypoints allows the drone to navigate through a series of predefined locations. This can be useful for tasks such as surveying, mapping, or automated inspections.

### Implementation Steps
1. **Define Waypoints**: Create a list of waypoints with coordinates (latitude, longitude, altitude).
2. **Waypoint Navigation Logic**: Implement logic to navigate from one waypoint to the next.
3. **MAVLink Commands**: Use MAVLink commands to send the waypoint coordinates to the drone.

## Altitude Control

### Overview
Altitude control involves adjusting the drone's altitude based on the detected blob's vertical position. This can help maintain a consistent distance from the target.

### Implementation Steps
1. **Vertical Offset Calculation**: Calculate the vertical offset of the blob from the center of the frame.
2. **Altitude Adjustment Logic**: Implement logic to adjust the drone's altitude based on the vertical offset.
3. **MAVLink Commands**: Use MAVLink commands to send the altitude adjustment to the drone.

## Obstacle Avoidance

### Overview
Obstacle avoidance involves detecting obstacles in the drone's path and adjusting its trajectory to avoid collisions. This can enhance the drone's navigation capabilities and ensure safe operation.

### Implementation Steps
1. **Obstacle Detection**: Use sensors (e.g., LiDAR, ultrasonic) to detect obstacles.
2. **Trajectory Adjustment Logic**: Implement logic to adjust the drone's trajectory based on the detected obstacles.
3. **MAVLink Commands**: Use MAVLink commands to send the adjusted trajectory to the drone.

## PID Regulator

### Overview
A PID (Proportional-Integral-Derivative) regulator can be used to improve the control of the drone's velocity and position by minimizing the error between the desired and actual positions.

### Implementation Steps
1. **Define PID Parameters**: Define the proportional, integral, and derivative gains.
2. **Error Calculation**: Calculate the error between the desired and actual positions.
3. **PID Control Logic**: Implement the PID control logic to adjust the drone's velocity based on the error.
4. **MAVLink Commands**: Use MAVLink commands to send the adjusted velocity to the drone.

These future directions aim to enhance the drone's capabilities by integrating waypoints, altitude control, and obstacle avoidance. Each feature involves specific implementation steps and the use of MAVLink commands to communicate with the drone.
