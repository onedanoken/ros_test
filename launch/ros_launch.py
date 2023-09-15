from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="ros_test",
            executable="talker",
            name="first_node"
        ),
        Node(
            package='ros_test',
            executable='listener',
            name='second_node'
        )
    ])