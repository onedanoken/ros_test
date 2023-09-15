import subprocess;

commands = ["bash -c 'cd ~/ros2_ws && colcon build && source install/setup.bash && ros2 launch ros_test ros_launch.py'"]

for command in commands:
    proc = subprocess.Popen(command, shell=True, executable="/bin/bash")
    proc.wait()