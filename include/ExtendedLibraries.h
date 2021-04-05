#include <iostream>
#include <thread>

/// <summary>
/// Variadic print function, outputs all parameters supplied. Works much like Python and Lua.
/// Parameters listed are not accurate, as this function uses fold expressions and templates.
/// </summary>
/// <typeparam name="Arg"></typeparam>
/// <typeparam name="...Args"></typeparam>
/// <param name="arg"></param>
/// <param name="...args"></param>
template <typename Arg, typename ...Args>
void print(Arg&& arg, Args&&... args) {
    std::cout << std::boolalpha;
    std::cout << std::forward<Arg>(arg);
    ((std::cout << ' ' << std::forward<Args>(args)), ...);
    std::cout << '\n';
}

/// <summary>
/// Yields the current thread for the duration specified.
/// </summary>
/// <param name="duration - Duration in milliseconds"></param>
void sleep(int duration) {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

/// <summary>
/// Gets the execution time of a function in milliseconds. Actual timings may be impacted
/// by using this function. If calls don't match the argument list, it's most likely that
/// you are not supplying the correct amount of parameters that the function to be called
/// (measured) takes.
/// </summary>
/// <typeparam name="...Args"></typeparam>
/// <param name="function - Function to be measured"></param>
/// <param name="...args - Arguments passed to the function"></param>
/// <returns>Returns a count (long long) of how long the function took</returns>
template<typename returnType, typename ...Args>
long long getExecutionTime(returnType (*function)(Args...), Args ...args) {
    auto start = std::chrono::high_resolution_clock::now();
    (*function)(args...);
    auto stop = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}
