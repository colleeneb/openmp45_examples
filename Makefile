CXX = clang++ 
CXXFLAGS = -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda
EXE = 02_target_construct 03_target_teams 03_target_teams_parallel \
      04_target_teams_distribute 04_target_teams_distribute_parallel \
      06_array_section 06_illegal_host_access 06_map 06_map_nested \
      06_map_sum 06_map_type 06_pointers 07_declare_target \
      08_target_data 09_target_update_data \
      10_target_enter_exit_data 11_nowait

all : $(EXE)

07_declare_target : 07_declare_target.cpp 07_declare_target2.cpp
	$(CXX) $(CXXFLAGS) -o $@ 07_declare_target.cpp 07_declare_target2.cpp

% : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXE)
