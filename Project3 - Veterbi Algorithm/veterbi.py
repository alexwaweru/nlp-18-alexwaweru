def viterbi(observations, states, start_probabilities, trans_probabilities, emit_probabilities):
    V = [{}]
    for state in states:
        V[0][state] = {"prob": start_probabilities[state] * emit_probabilities[state][observations[0]], "prev": None}
    for t in range(1, len(observations)):
        V.append({})
        for state in states:
            max_tr_prob = max(V[t-1][prev_st]["prob"]*trans_probabilities[prev_st][state] for prev_st in states)
            for prev_st in states:
                if V[t-1][prev_st]["prob"] * trans_probabilities[prev_st][state] == max_tr_prob:
                    max_prob = max_tr_prob * emit_probabilities[state][observations[t]]
                    V[t][state] = {"prob": max_prob, "prev": prev_st}
                    break
    for line in portable_tag_seq_table(V):
        print (line)
    opt = []
    max_prob = max(value["prob"] for value in V[-1].values())
    previous = None
    for st, data in V[-1].items():
        if data["prob"] == max_prob:
            opt.append(st)
            previous = st
            break
    for t in range(len(V) - 2, -1, -1):
        opt.insert(0, V[t + 1][previous]["prev"])
        previous = V[t + 1][previous]["prev"]
    print(opt)

def portable_tag_seq_table(V):
    for state in V[0]:
        yield("%.7s: " % state + " ".join("%.7s" % ("%f" % v[state]["prob"]) for v in V))


observations = ('back', 'the', 'bill')
states = ('NNP', 'MD', 'VB', 'JJ', 'NN', 'RB', 'DT')
start_probabilities = {'NNP':0.2767, 'MD':0.0006, 'VB':0.0031, 'JJ':0.0453, 'NN':0.0449, 'RB':0.0510, 'DT':0.2026}
trans_probabilities = {
   'NNP' : {'NNP':0.3777, 'MD':0.0110, 'VB':0.0009, 'JJ':0.0084, 'NN':0.0584, 'RB':0.0090, 'DT':0.0025},
   'MD' : {'NNP':0.0008, 'MD':0.0002, 'VB':0.7968, 'JJ':0.0005, 'NN':0.0008, 'RB':0.1698, 'DT':0.0041},
   'VB' : {'NNP':0.0322, 'MD':0.0005, 'VB':0.0050, 'JJ':0.0837, 'NN':0.0615, 'RB':0.0514, 'DT':0.2231},
   'JJ' : {'NNP':0.0366, 'MD':0.0004, 'VB':0.0001, 'JJ':0.0733, 'NN':0.4509, 'RB':0.0036, 'DT':0.0036},
   'NN' : {'NNP':0.0096, 'MD':0.0176, 'VB':0.0014, 'JJ':0.0086, 'NN':0.1216, 'RB':0.0177, 'DT':0.0068},
   'RB' : {'NNP':0.0068, 'MD':0.0102, 'VB':0.1011, 'JJ':0.1012, 'NN':0.0120, 'RB':0.0728, 'DT':0.0479},
   'DT' : {'NNP':0.1147, 'MD':0.0021, 'VB':0.0002, 'JJ':0.2157, 'NN':0.4744, 'RB':0.0102, 'DT':0.0017}
   }
emit_probabilities = {
   'NNP' : {'back': 0, 'the': 0.000048, 'bill': 0},
   'MD' : {'back': 0, 'the': 0, 'bill': 0},
   'VB' : {'back': 0.000672, 'the': 0, 'bill': 0.000028},
   'JJ' : {'back': 0.000340, 'the': 0, 'bill': 0},
   'NN' : {'back': 0.000223, 'the': 0, 'bill': 0.002337},
   'RB' : {'back': 0.010446, 'the': 0, 'bill': 0},
   'DT' : {'back': 0, 'the': 0.506099, 'bill': 0}
   }
viterbi(observations, states, start_probabilities, trans_probabilities, emit_probabilities)