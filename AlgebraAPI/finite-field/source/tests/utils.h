template <typename num>
num getRandomNumber(num rangeStart, num rangeEnd)
{
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(rangeStart, rangeEnd);

    return static_cast<num>(distr(gen));
}