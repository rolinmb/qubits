using System;
using System.IO.Compression;
using System.Linq;

public class Qudit
{
    public double[] Amplitudes { get; private set; }

    public Qudit(params double[] ampls)
    {
        Amplitudes = ampls;
        Validate();
    }

    private void Validate()
    {
        double totalProb = Amplitudes.Sum(a => Math.Pow(a, 2));
        if (Math.Round(totalProb, 10) != 1.0)
        {
            throw new ArgumentException($"Qudit.Validte() :: Qudit outcome probabilitied do not sum to 1.0 or 100%, have {totalProb}");
        }
    }

    public int Measure(Random rand)
    {
        double obs = rand.NextDouble();
        double cumulativeProb = 0;

        for (int i = 0; i < Amplitudes.Length; i++)
        {
            cumulativeProb += Math.Pow(Amplitudes[i], 2);
            if (obs < cumulativeProb)
            {
                return i;
            }
        }
        return -1; // should not reach, likely Amplitudes arent valid
    }

    public void ResetAmplitudes(params double[] ampls)
    {
        Amplitudes = ampls;
        Validate();
    }
}

public class QuantumRegister
{
    public List<Qudit> Qudits { get; private set; }
    
    public QuantumRegister(params Qudit[] qudits)
    {
        Qudits = new List<Qudit>(qudits);
    }

    public int[] Measure(Random rand)
    {
        int[] results = new int[Qudits.Count];

        for (int i = 0; i < Qudits.Count; i++)
        {
            results[i] = Qudits[i].Measure(rand);
        }

        return results;
    }
}


class Program
{
    static void Main(string[] args)
    {
        Random rand = new Random();

        Qudit qudit1 = new Qudit(0.5, Math.Sqrt(3) / 2); // 25% chance for 0, 75% for 1
        Qudit qudit2 = new Qudit(0.5, 0.5, Math.Sqrt(2) / 2); // 25% chance for 0 or 1, 50% for 2

        QuantumRegister qr = new QuantumRegister(qudit1, qudit2);

        int iterations = 10000;
        int[] nqd1Zeros = new int[2]; // For qudit1 (0, 1)
        int[] nqd2Zeros = new int[3]; // For qudit2 (0, 1, 2)

        for (int n = 0; n < iterations; n++)
        {
            int[] measurement = qr.Measure(rand);
            nqd1Zeros[measurement[0]]++;
            nqd2Zeros[measurement[1]]++;
        }

        Console.WriteLine($"Quantum Register Measurement Test Results after {iterations} Iterations:");
        Console.WriteLine($"\tqudit1 -> {nqd1Zeros[0]} Zeros observed; {nqd1Zeros[1]} Ones observed.");
        Console.WriteLine($"\tqudit2 -> {nqd2Zeros[0]} Zeros observed; {nqd2Zeros[1]} Ones observed; {nqd2Zeros[2]} Twos observed.");
    }
}