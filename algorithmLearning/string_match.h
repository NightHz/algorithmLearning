#pragma once
int native_string_match(const char* str,const char* pattern)
{
	for (int i = 0; true; i++)
	{
		for (int j = 0; true; j++)
			if (pattern[j] == 0)
				return i;
			else if (str[i + j] == 0)
				return -1;
			else if (pattern[j] != str[i + j])
				break;
	}
}

void KMP_prefix(const char* pattern, int* pi)
{
	pi[0] = -1;
	for (int j = 1; pattern[j] != 0; j++)
	{
		int k = pi[j - 1];
		while (k != -1 && pattern[j - 1] != pattern[k])
			k = pi[k];
		pi[j] = k + 1;
	}
	for (int j = 1; pattern[j] != 0; j++)
	{
		if (pattern[j] == pattern[pi[j]])
			pi[j] = pi[pi[j]];
	}
}
int KMP_string_match(const char* str, const char* pattern)
{
	int pi_size;
	for (pi_size = 0; pattern[pi_size] != 0; pi_size++)
		;
	if (pi_size == 0)
		return 0;
	int* pi = new int[pi_size];
	KMP_prefix(pattern, pi);
	for (int i = 0, j = 0; true;)
	{
		if (pattern[j] == 0)
		{
			delete[] pi;
			return i - j;
		}
		else if (str[i] == 0)
		{
			delete[] pi;
			return -1;
		}
		if (pattern[j] == str[i])
			i++, j++;
		else if (pi[j] == -1)
			i++, j = 0;
		else
			j = pi[j];
	}
}