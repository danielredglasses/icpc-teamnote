random_device rd;
mt19937 gen(rd());
cout << gen() << " "; // raw output of the generator. 0~2^32-1
uniform_int_distribution<> dist(1,6); // distribute results between 1 and 6 inclusive.
cout << dist(gen) << " "; // pass the generator to the distribution.
shuffle(all(arr), gen);
