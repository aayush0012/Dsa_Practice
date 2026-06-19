/*
    ============================================================
     Task Scheduler
    ============================================================

    THOUGHT PROCESS (Simple English + Hinglish)

    Problem:
    Hume tasks diye gaye hain (A-Z) aur ek cooldown time n.
    Agar humne kisi task ko abhi execute kiya hai, to usi task ko
    dobara execute karne se pehle kam se kam n intervals ka gap
    hona chahiye.

    Example:
    Tasks = [A,A,A,B,B,B], n = 2

    A karne ke baad next A directly nahi kar sakte.
    Beech mein 2 intervals ka gap chahiye.

    ------------------------------------------------------------
    OBSERVATION
    ------------------------------------------------------------

    Har time par hume woh task execute karna chahiye jiska
    frequency sabse zyada bacha hua hai.

    Kyun?

    Kyunki high frequency task ko delay karne se future mein
    zyada idle intervals aa sakte hain.

    Isliye:
    - Maximum remaining frequency wala task jaldi execute karo.
    - Iske liye Max Heap (Priority Queue) use karenge.

    ------------------------------------------------------------
    COOLDOWN PROBLEM
    ------------------------------------------------------------

    Maan lo humne task A execute kiya.

    A ko turant heap mein wapas nahi daal sakte,
    warna woh fir se select ho sakta hai.

    Isliye usse ek cooldown queue mein bhejenge.

    Queue store karegi:

        {remaining_frequency, available_time}

    Example:

        current_time = 0
        execute A

        remaining freq = 2

        available again at:
        current_time + n + 1

        = 0 + 2 + 1
        = 3

    Queue:
        {2, 3}

    ------------------------------------------------------------
    SIMULATION
    ------------------------------------------------------------

    Har interval par:

    1. Check karo ki koi task cooldown complete kar chuka hai?
       Agar haan, usse heap mein wapas daal do.

    2. Agar heap empty hai:
       -> CPU idle rahega
       -> time++

    3. Agar heap empty nahi hai:
       -> Max frequency task nikalo
       -> Execute karo
       -> Frequency reduce karo
       -> Agar abhi bhi remaining frequency > 0 hai
          to cooldown queue mein bhej do

    4. time++

    ------------------------------------------------------------
    DATA STRUCTURES
    ------------------------------------------------------------

    Priority Queue:
        Stores frequencies of tasks ready to execute.

    Queue:
        Stores tasks currently cooling down.

    visited[26]:
        Frequency count of A-Z.

    ------------------------------------------------------------
    TIME COMPLEXITY
    ------------------------------------------------------------

    Let T = total number of tasks.

    Heap size maximum 26 hi ho sakti hai
    (sirf A-Z tasks).

    Har task limited number of times heap mein jaata hai.

    Time Complexity:
        O(T log 26)

    Since log(26) is constant:

        O(T)

    Space Complexity:
        O(26)

        => O(1)

    ============================================================
*/

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        priority_queue<int> pq;
        vector<int> visited(26, 0);
        queue<pair<int, int>> q;

        // Count frequencies
        for (int i = 0; i < tasks.size(); i++) {
            visited[tasks[i] - 'A']++;
        }

        // Push all frequencies into max heap
        for (int i = 0; i < 26; i++) {
            if (visited[i] > 0)
                pq.push(visited[i]);
        }

        int time = 0;

        while (!pq.empty() || !q.empty()) {

            // Bring back tasks whose cooldown is over
            while (!q.empty() && q.front().second == time) {
                pq.push(q.front().first);
                q.pop();
            }

            // Idle interval
            if (pq.empty()) {
                time++;
                continue;
            }

            // Execute task with highest remaining frequency
            int max_freq = pq.top();
            pq.pop();

            max_freq--;

            // Still remaining occurrences
            if (max_freq > 0) {
                q.push({max_freq, time + n + 1});
            }

            time++;
        }

        return time;
    }
};
