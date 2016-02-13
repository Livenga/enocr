__kernel void
hello(void) {
  const int idx_x = get_global_id(0), idx_y = get_global_id(1);

  printf("%3dx%3d\n", idx_x, idx_y);
}
