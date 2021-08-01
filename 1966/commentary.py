from random import sample

docs = sample(range(1000), 20)
Q = docs[:]
printed = []

while Q:
    print(printed, Q)
    if any(Q[0] < doc for doc in Q[1:]):
        # Q 내에서 중요도가 가장 큰 문서가 아니면 출력되지 못한다.
        Q.append(Q.pop(0))
    else:
        # (대우) 출력된 문서는 Q 내에서 중요도가 가장 큰 문서다.
        printed.append(Q.pop(0))

# 중요도가 가장 높은것을 하나씩 뺐으니, 결국 정렬이나 마찬가지이다.
print(printed, Q)
print()
print(printed == sorted(docs, reverse=True))
