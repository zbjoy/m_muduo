# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zbjoy/cpp_code/muduo_learn/my_muduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zbjoy/cpp_code/muduo_learn/my_muduo/build

# Include any dependencies generated for this target.
include CMakeFiles/my_muduo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_muduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_muduo.dir/flags.make

CMakeFiles/my_muduo.dir/Acceptor.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Acceptor.o: ../Acceptor.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_muduo.dir/Acceptor.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/Acceptor.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/Acceptor.cc

CMakeFiles/my_muduo.dir/Acceptor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Acceptor.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/Acceptor.cc > CMakeFiles/my_muduo.dir/Acceptor.i

CMakeFiles/my_muduo.dir/Acceptor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Acceptor.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/Acceptor.cc -o CMakeFiles/my_muduo.dir/Acceptor.s

CMakeFiles/my_muduo.dir/Buffer.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Buffer.o: ../Buffer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_muduo.dir/Buffer.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/Buffer.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/Buffer.cc

CMakeFiles/my_muduo.dir/Buffer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Buffer.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/Buffer.cc > CMakeFiles/my_muduo.dir/Buffer.i

CMakeFiles/my_muduo.dir/Buffer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Buffer.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/Buffer.cc -o CMakeFiles/my_muduo.dir/Buffer.s

CMakeFiles/my_muduo.dir/Channel.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Channel.o: ../Channel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_muduo.dir/Channel.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/Channel.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/Channel.cc

CMakeFiles/my_muduo.dir/Channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Channel.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/Channel.cc > CMakeFiles/my_muduo.dir/Channel.i

CMakeFiles/my_muduo.dir/Channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Channel.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/Channel.cc -o CMakeFiles/my_muduo.dir/Channel.s

CMakeFiles/my_muduo.dir/CurrentThread.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/CurrentThread.o: ../CurrentThread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_muduo.dir/CurrentThread.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/CurrentThread.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/CurrentThread.cc

CMakeFiles/my_muduo.dir/CurrentThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/CurrentThread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/CurrentThread.cc > CMakeFiles/my_muduo.dir/CurrentThread.i

CMakeFiles/my_muduo.dir/CurrentThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/CurrentThread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/CurrentThread.cc -o CMakeFiles/my_muduo.dir/CurrentThread.s

CMakeFiles/my_muduo.dir/DefaultPoller.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/DefaultPoller.o: ../DefaultPoller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_muduo.dir/DefaultPoller.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/DefaultPoller.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/DefaultPoller.cc

CMakeFiles/my_muduo.dir/DefaultPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/DefaultPoller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/DefaultPoller.cc > CMakeFiles/my_muduo.dir/DefaultPoller.i

CMakeFiles/my_muduo.dir/DefaultPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/DefaultPoller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/DefaultPoller.cc -o CMakeFiles/my_muduo.dir/DefaultPoller.s

CMakeFiles/my_muduo.dir/EPollPoller.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/EPollPoller.o: ../EPollPoller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_muduo.dir/EPollPoller.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/EPollPoller.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/EPollPoller.cc

CMakeFiles/my_muduo.dir/EPollPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/EPollPoller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/EPollPoller.cc > CMakeFiles/my_muduo.dir/EPollPoller.i

CMakeFiles/my_muduo.dir/EPollPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/EPollPoller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/EPollPoller.cc -o CMakeFiles/my_muduo.dir/EPollPoller.s

CMakeFiles/my_muduo.dir/EventLoop.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/EventLoop.o: ../EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/my_muduo.dir/EventLoop.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/EventLoop.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoop.cc

CMakeFiles/my_muduo.dir/EventLoop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/EventLoop.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoop.cc > CMakeFiles/my_muduo.dir/EventLoop.i

CMakeFiles/my_muduo.dir/EventLoop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/EventLoop.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoop.cc -o CMakeFiles/my_muduo.dir/EventLoop.s

CMakeFiles/my_muduo.dir/EventLoopThread.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/EventLoopThread.o: ../EventLoopThread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/my_muduo.dir/EventLoopThread.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/EventLoopThread.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoopThread.cc

CMakeFiles/my_muduo.dir/EventLoopThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/EventLoopThread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoopThread.cc > CMakeFiles/my_muduo.dir/EventLoopThread.i

CMakeFiles/my_muduo.dir/EventLoopThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/EventLoopThread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoopThread.cc -o CMakeFiles/my_muduo.dir/EventLoopThread.s

CMakeFiles/my_muduo.dir/EventLoopThreadPool.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/EventLoopThreadPool.o: ../EventLoopThreadPool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/my_muduo.dir/EventLoopThreadPool.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/EventLoopThreadPool.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoopThreadPool.cc

CMakeFiles/my_muduo.dir/EventLoopThreadPool.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/EventLoopThreadPool.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoopThreadPool.cc > CMakeFiles/my_muduo.dir/EventLoopThreadPool.i

CMakeFiles/my_muduo.dir/EventLoopThreadPool.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/EventLoopThreadPool.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/EventLoopThreadPool.cc -o CMakeFiles/my_muduo.dir/EventLoopThreadPool.s

CMakeFiles/my_muduo.dir/InetAddress.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/InetAddress.o: ../InetAddress.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/my_muduo.dir/InetAddress.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/InetAddress.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/InetAddress.cc

CMakeFiles/my_muduo.dir/InetAddress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/InetAddress.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/InetAddress.cc > CMakeFiles/my_muduo.dir/InetAddress.i

CMakeFiles/my_muduo.dir/InetAddress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/InetAddress.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/InetAddress.cc -o CMakeFiles/my_muduo.dir/InetAddress.s

CMakeFiles/my_muduo.dir/Logger.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Logger.o: ../Logger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/my_muduo.dir/Logger.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/Logger.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/Logger.cc

CMakeFiles/my_muduo.dir/Logger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Logger.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/Logger.cc > CMakeFiles/my_muduo.dir/Logger.i

CMakeFiles/my_muduo.dir/Logger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Logger.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/Logger.cc -o CMakeFiles/my_muduo.dir/Logger.s

CMakeFiles/my_muduo.dir/Poller.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Poller.o: ../Poller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/my_muduo.dir/Poller.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/Poller.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/Poller.cc

CMakeFiles/my_muduo.dir/Poller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Poller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/Poller.cc > CMakeFiles/my_muduo.dir/Poller.i

CMakeFiles/my_muduo.dir/Poller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Poller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/Poller.cc -o CMakeFiles/my_muduo.dir/Poller.s

CMakeFiles/my_muduo.dir/Socket.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Socket.o: ../Socket.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/my_muduo.dir/Socket.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/Socket.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/Socket.cc

CMakeFiles/my_muduo.dir/Socket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Socket.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/Socket.cc > CMakeFiles/my_muduo.dir/Socket.i

CMakeFiles/my_muduo.dir/Socket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Socket.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/Socket.cc -o CMakeFiles/my_muduo.dir/Socket.s

CMakeFiles/my_muduo.dir/TcpConnection.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/TcpConnection.o: ../TcpConnection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/my_muduo.dir/TcpConnection.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/TcpConnection.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/TcpConnection.cc

CMakeFiles/my_muduo.dir/TcpConnection.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/TcpConnection.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/TcpConnection.cc > CMakeFiles/my_muduo.dir/TcpConnection.i

CMakeFiles/my_muduo.dir/TcpConnection.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/TcpConnection.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/TcpConnection.cc -o CMakeFiles/my_muduo.dir/TcpConnection.s

CMakeFiles/my_muduo.dir/TcpServer.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/TcpServer.o: ../TcpServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/my_muduo.dir/TcpServer.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/TcpServer.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/TcpServer.cc

CMakeFiles/my_muduo.dir/TcpServer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/TcpServer.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/TcpServer.cc > CMakeFiles/my_muduo.dir/TcpServer.i

CMakeFiles/my_muduo.dir/TcpServer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/TcpServer.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/TcpServer.cc -o CMakeFiles/my_muduo.dir/TcpServer.s

CMakeFiles/my_muduo.dir/Thread.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Thread.o: ../Thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/my_muduo.dir/Thread.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/Thread.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/Thread.cc

CMakeFiles/my_muduo.dir/Thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/Thread.cc > CMakeFiles/my_muduo.dir/Thread.i

CMakeFiles/my_muduo.dir/Thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/Thread.cc -o CMakeFiles/my_muduo.dir/Thread.s

CMakeFiles/my_muduo.dir/Timestamp.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Timestamp.o: ../Timestamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/my_muduo.dir/Timestamp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_muduo.dir/Timestamp.o -c /home/zbjoy/cpp_code/muduo_learn/my_muduo/Timestamp.cc

CMakeFiles/my_muduo.dir/Timestamp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Timestamp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zbjoy/cpp_code/muduo_learn/my_muduo/Timestamp.cc > CMakeFiles/my_muduo.dir/Timestamp.i

CMakeFiles/my_muduo.dir/Timestamp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Timestamp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zbjoy/cpp_code/muduo_learn/my_muduo/Timestamp.cc -o CMakeFiles/my_muduo.dir/Timestamp.s

# Object files for target my_muduo
my_muduo_OBJECTS = \
"CMakeFiles/my_muduo.dir/Acceptor.o" \
"CMakeFiles/my_muduo.dir/Buffer.o" \
"CMakeFiles/my_muduo.dir/Channel.o" \
"CMakeFiles/my_muduo.dir/CurrentThread.o" \
"CMakeFiles/my_muduo.dir/DefaultPoller.o" \
"CMakeFiles/my_muduo.dir/EPollPoller.o" \
"CMakeFiles/my_muduo.dir/EventLoop.o" \
"CMakeFiles/my_muduo.dir/EventLoopThread.o" \
"CMakeFiles/my_muduo.dir/EventLoopThreadPool.o" \
"CMakeFiles/my_muduo.dir/InetAddress.o" \
"CMakeFiles/my_muduo.dir/Logger.o" \
"CMakeFiles/my_muduo.dir/Poller.o" \
"CMakeFiles/my_muduo.dir/Socket.o" \
"CMakeFiles/my_muduo.dir/TcpConnection.o" \
"CMakeFiles/my_muduo.dir/TcpServer.o" \
"CMakeFiles/my_muduo.dir/Thread.o" \
"CMakeFiles/my_muduo.dir/Timestamp.o"

# External object files for target my_muduo
my_muduo_EXTERNAL_OBJECTS =

../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Acceptor.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Buffer.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Channel.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/CurrentThread.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/DefaultPoller.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/EPollPoller.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/EventLoop.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/EventLoopThread.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/EventLoopThreadPool.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/InetAddress.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Logger.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Poller.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Socket.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/TcpConnection.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/TcpServer.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Thread.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Timestamp.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/build.make
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX shared library ../lib/libmy_muduo.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_muduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_muduo.dir/build: ../lib/libmy_muduo.so

.PHONY : CMakeFiles/my_muduo.dir/build

CMakeFiles/my_muduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_muduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_muduo.dir/clean

CMakeFiles/my_muduo.dir/depend:
	cd /home/zbjoy/cpp_code/muduo_learn/my_muduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zbjoy/cpp_code/muduo_learn/my_muduo /home/zbjoy/cpp_code/muduo_learn/my_muduo /home/zbjoy/cpp_code/muduo_learn/my_muduo/build /home/zbjoy/cpp_code/muduo_learn/my_muduo/build /home/zbjoy/cpp_code/muduo_learn/my_muduo/build/CMakeFiles/my_muduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_muduo.dir/depend

