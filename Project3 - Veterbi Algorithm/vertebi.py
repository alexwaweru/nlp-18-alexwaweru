
def viterbi(obs, states, start_p, trans_p, emit_p):
 2 
    V = [{}]
 3 
    for st in states:
 4 
        V[0][st] = {"prob": start_p[st] * emit_p[st][obs[0]], "prev": None}
 5 
    # Run Viterbi when t > 0
 6 
    for t in range(1, len(obs)):
 7 
        V.append({})
 8 
        for st in states:
 9 
            max_tr_prob = max(V[t-1][prev_st]["prob"]*trans_p[prev_st][st] for prev_st in states)
10 
            for prev_st in states:
11 
                if V[t-1][prev_st]["prob"] * trans_p[prev_st][st] == max_tr_prob:
12 
                    max_prob = max_tr_prob * emit_p[st][obs[t]]
13 
                    V[t][st] = {"prob": max_prob, "prev": prev_st}
14 
                    break
15 
    for line in dptable(V):
16 
        print line
17 
    opt = []
18 
    # The highest probability
19 
    max_prob = max(value["prob"] for value in V[-1].values())
20 
    previous = None
21 
    # Get most probable state and its backtrack
22 
    for st, data in V[-1].items():
23 
        if data["prob"] == max_prob:
24 
            opt.append(st)
25 
            previous = st
26 
            break
27 
    # Follow the backtrack till the first observation
28 
    for t in range(len(V) - 2, -1, -1):
29 
        opt.insert(0, V[t + 1][previous]["prev"])
30 
        previous = V[t + 1][previous]["prev"]
31 

32 
    print 'The steps of states are ' + ' '.join(opt) + ' with highest probability of %s' % max_prob
33 

34 
def dptable(V):
35 
    # Print a table of steps from dictionary
36 
    yield " ".join(("%12d" % i) for i in range(len(V)))
37 
    for state in V[0]:
38 
        yield "%.7s: " % state + " ".join("%.7s" % ("%f" % v[state]["prob"]) for v in V)
