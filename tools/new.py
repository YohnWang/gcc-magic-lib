for i in range(2,33):
    print(f"#define _g_new_{i}(...) _g_new_with_init(__VA_ARGS__)")