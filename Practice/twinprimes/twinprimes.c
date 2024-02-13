int twin_primes(int a, int b)
{
	int count = 0;
	for(int i = a; i + 2 <= b; i++)
	{
		if(isprime(i) && isprime(i + 2))
		count ++;
	}
	return count;
}