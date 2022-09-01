for i in range(2,65):
    print(f'#define throw_{i}(...) throw_vaargs(__VA_ARGS__)')