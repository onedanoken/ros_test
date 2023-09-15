from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package="ros_test",
            executable="talker",
            name="first_node",
            output="screen",
            emulate_tty=True,
            parameters=[
                "/home/iurbanovitch/ros2_ws/src/ros_test \
                /params/first_node.yaml"
            ]
        ),
        Node(
            package='ros_test',
            executable='listener',
            name='second_node',
            output="screen",
            emulate_tty=True,
            parameters=[
                "/home/iurbanovitch/ros2_ws/src/ros_test \
                /params/second_node.yaml"
            ]
        )
    ])
