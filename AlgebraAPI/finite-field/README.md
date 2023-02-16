## This document is written to help students organise their work throgh group project for universal algebra class

### Code commiting, review and pushing
1) Code commits via git should follow [this](https://waitng-for-zhereb-respond.com/) rules
2) Each new feature must be followed by set of tests. How to design test you can find bellow
3) After set of features is implemented, pull requests can be created. 
Do not forget to sync your project before doing this 
4) Code will be reviewed in 1-2 days and either merged or declined with comments what needs to be changed

### Code style, test and API design 
1. Code style should follow  [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
2. Public API usualy will be prewritten, but if some changes needed, contact student responsible for API design 
3. Tests design:
    * Use doctest.h for testing 
    * Input types:
        - Regular input from user
        - From file 
        - Randomly generated
    * Edge (border) cases must be tested especially thoroughly

