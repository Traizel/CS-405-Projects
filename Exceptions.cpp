// CS 405 Module Four Exceptions Activity

#include <exception>
#include <iostream>
#include <stdexcept>

// Give application-specific failures their own standard exception subtype.
class ApplicationException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "A custom application error occurred.";
    }
};

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;
    // Simulate a standard exception so the caller can demonstrate recovery.
    throw std::runtime_error("Even more custom application logic failed.");
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;
    // Handle this failure locally and continue with the remaining logic.
    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& error)
    {
        std::cout << "Standard exception caught: " << error.what() << std::endl;
    }

    std::cout << "Leaving Custom Application Logic." << std::endl;
    // Propagate this distinct failure to the explicit handler in main.
    throw ApplicationException{};
}

float divide(float num, float den)
{
    // Floating-point division does not automatically throw a C++ exception.
    // Reject positive and negative zero before evaluating the division.
    if (den == 0.0f)
    {
        throw std::invalid_argument("Cannot divide by zero.");
    }
    return num / den;
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0.0f;

    // Catch only the exception type intentionally thrown by divide.
    try
    {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator
                  << ") = " << result << std::endl;
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Division exception caught: " << error.what() << std::endl;
    }
}

int main()
{
    // Order handlers from the most specific type to the broadest fallback.
    try
    {
        std::cout << "Exceptions Tests!" << std::endl;
        do_division();
        do_custom_application_logic();
    }
    catch (const ApplicationException& error)
    {
        std::cout << "Custom exception caught in main: " << error.what() << std::endl;
    }
    catch (const std::exception& error)
    {
        std::cout << "Standard exception caught in main: " << error.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        // An unknown exception has no guaranteed what() interface.
        std::cout << "Unknown exception caught in main." << std::endl;
        return 1;
    }
    // The intentional demonstration exceptions have been handled.
    return 0;
}
