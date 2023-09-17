from setuptools import find_packages, setup

package_name = 'ros_python'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='iurbanovitch',
    maintainer_email='urbanovitchiv@yandex.ru',
    description='Two Nodes Python',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'talker = ros_python.first_node:main',
            'listener = ros_python.second_node:main',
        ],
    },
)
