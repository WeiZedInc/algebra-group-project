using System.Runtime.InteropServices;
using System.Text;

namespace AlgebraWASM.Client
{
	public static class PolinomialParser
	{
		public static unsafe byte** ParsePolynomial(string polynomial, out int size)
		{
			polynomial = polynomial.Replace(" ", "");

			int maxDegree = GetMaxDegree(polynomial);

			byte[] coefficients = new byte[maxDegree + 1];

			string[] terms = polynomial.Split('+', '-');
			size = terms.Length / 2;

			foreach (string term in terms)
			{
				if (string.IsNullOrEmpty(term))
					continue;

				int sign = (term[0] == '-') ? -1 : 1;

				string termValue = term.TrimStart('-', '+');

				string[] parts = termValue.Split('x');

				byte coefficient = 0;
				int degree = 0;

				if (parts[0] == string.Empty || parts[0] == "+")
					coefficient = (byte)sign;
				else
					coefficient = (byte)(sign * byte.Parse(parts[0]));

				if (parts.Length > 1)
				{
					if (parts[1] == string.Empty)
						degree = 1;
					else
						degree = int.Parse(parts[1].TrimStart('^'));
				}

				coefficients[degree] += coefficient;
			}

			byte** result = (byte**)Marshal.AllocHGlobal((maxDegree + 1) * sizeof(byte*));

			for (int i = 0; i <= maxDegree; i++)
			{
				byte* coeffPtr = (byte*)Marshal.AllocHGlobal(sizeof(byte));
				*coeffPtr = coefficients[i];
				result[i] = coeffPtr;
			}
			
			return result;
		}

		public static unsafe string ParsePolynomial(byte** coefficients)
		{
			StringBuilder polynomial = new StringBuilder();

			int size = 0;
			while (coefficients[size] != null)
				size++;

			for (int i = size - 1; i >= 0; i--)
			{
				byte coefficient = *coefficients[i];
				if (coefficient != 0)
				{
					if (coefficient > 0 && i != size - 1)
						polynomial.Append("+");

					if (coefficient != 1 || i == 0)
						polynomial.Append(coefficient);

					if (i > 0)
					{
						polynomial.Append("x");

						if (i > 1)
							polynomial.Append("^" + i);
					}
				}
			}

			return polynomial.ToString();
		}

		private static int GetMaxDegree(string polynomial)
		{
			int maxDegree = 0;

			string[] terms = polynomial.Split('+', '-');

			foreach (string term in terms)
			{
				if (string.IsNullOrEmpty(term))
					continue;

				string[] parts = term.Split('x');

				if (parts.Length > 1)
				{
					int degree = 0;
					if (parts[1] == string.Empty)
						degree = 1;
					else
						degree = int.Parse(parts[1].TrimStart('^'));

					if (degree > maxDegree)
						maxDegree = degree;
				}
			}

			return maxDegree;
		}
	}
}
