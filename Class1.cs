using System;
using System.Collections.Generic;
using System.Linq;
public class Class1 {
    static Dictionary<String, int> dic;
    static void Input() {
        int nub = int.Parse(Console.ReadLine());
        dic = new Dictionary<string, int>(nub * 2);
        for (int i = 0; i < nub; i++) {
            string[] s = Console.ReadLine().Split(' ');
            for (int j = 0; j < s.Length; j++) {
                if (dic.ContainsKey(s[j])) dic[s[j]]++;
                else dic.Add(s[j], 1);
            }
        }
    }
    static void Main(string[] args) {
        Input();
        var a = from r in dic.AsParallel() orderby r.Value descending, r.Key select r;
        int temp = 0, num = 0;
        foreach (var item in a) {
            if (num == 0) {
                temp = item.Value;
                Console.Write(item.Key + " " + item.Value);
            }
            if (item.Value == temp) num++;
            else {
                if (num > 1) Console.WriteLine(" " + num);
                else Console.WriteLine();
                break;
            }
        }
    }
}

