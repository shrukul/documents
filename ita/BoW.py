import nltk

positiveWords = {}

positiveWords['good'] = 1
positiveWords['great'] = 1.5
positiveWords['awesome'] = 2.0
positiveWords['amazing'] = 2.0
positiveWords['worth'] = 2.5


negativeWords = {}

negativeWords['bad'] = 1
negativeWords['worst'] = 2.0
negativeWords['worse'] = 2.0
negativeWords['not worth'] = 2.5


review = "This is a very good product. Worth buying."
total_score = 0

lower_review = review.lower()

tokens = nltk.word_tokenize(lower_review)
tagged_tokens = nltk.pos_tag(tokens)
print type(tagged_tokens)

print tagged_tokens

chunk_grammar = "NP: {<JJ>+<NN>}"
chunk_parser = nltk.RegexpParser(chunk_grammar)
chunk_tree = chunk_parser.parse(tagged_tokens)


hel = []
#print chunk_tree
#np = ["".join(str(subtree.leaves())) for subtree in chunk_tree.subtrees() if subtree.label() == 'NP']
np = [hel.append(subtree.leaves()) for subtree in chunk_tree.subtrees() if subtree.label() == 'NP']
print hel

for sent in hel:
    for (word,tag) in sent.items():
        print word
#    for [word,tag) in sent:
#       print word

adjectives = []

for (word,tag) in tagged_tokens:
	if(tag == 'JJ'):
		adjectives.append(word)

for adj in adjectives:
    if (adj in positiveWords):
	    total_score += positiveWords[adj]

    elif (adj in negativeWords):
        total_score -= negativeWords[adj]

print total_score
