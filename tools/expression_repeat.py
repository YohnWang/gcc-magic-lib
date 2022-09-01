
def gen(i):
    s = f"""#define _g_expression_repeat_{i}(...)  _g_expression_repeat_{i-1}(__VA_ARGS__) __VA_ARGS__"""
    print(s)

for i in range(2,65):
    gen(i)