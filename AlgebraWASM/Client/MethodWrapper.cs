using System.Runtime.InteropServices;

namespace AlgebraWASM.Client
{
    public enum FinitiFieldMethods
    {
		addition = 1,
        subtraction,
        multiplication,
        division,
        fastPow,
        inverse,
        factorizePolard,
        factorizeSimple,
        discreteSqrt,
        discreteLog,
        orderOfElement,
        isGenerator,
        CarmichaelFunction,
        isPrime
    }

    public static class MethodWrapper
    {
        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* addition(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* subtraction(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* multiplication(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* division(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* fastPow(byte* a, byte* degree, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* inverse(byte* num, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte factorizePolard(ref UInt64 size, byte* num, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte factorizeSimple(ref UInt64 size, byte* num, byte* mode, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte** discreteSqrt(byte* num, byte* mode, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* discreteLog(byte* num, byte* basa, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* orderOfElement(byte* num, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern bool isGenerator(byte* num, byte* mod, byte* errStr); 

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* CarmichaelFunction(byte* num, byte* mod, byte* errStr); 

        [DllImport("finite-field-wrapper")]
        public static unsafe extern bool isPrime(byte* num, byte* mod, byte* iterations, byte* errStr);
    }
}