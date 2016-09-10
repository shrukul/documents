import nltk

text = """Awesome phone at Rs.4500. Obviously, GSMArena puts this phone as one of the hottest models out there and that is so true. It came in a neat packaging (thanks to Cloudtail) and the in-box accessories include headset, charger, and phone guide. The one thing that is so needed but missing in the box is the data transfer cable. I had a samsung data cable and am using it with the phone. Have been using it since 17th October, and here is my take on it:
Battery: the 2390mAH is seriously great and after playing games like Temple Run2, Angry Birds for more than an hour, and browsing as well as talking for 3 hours, the remaining battery was 40%. That is seriously good performance.
Screen: The screen is perfect and there are ways to adjust the screen brightness, which itself is a battery saver. If the brightness is too low then the screen is not visible in the sunlight.
Speakers: The speakers are good. They don't sound dolby but the music or loudspeaker calls are crystal clear. The same goes for the headset. I am using a JBL and the sound really comes out pretty nice.
Camera: It is 5MP and thats what you get. Daylight pics are great although night pics are hazy.
Apps: It comes with built in apps, which take up about 2GB of space. You can download more apps like the cleanmaster to keep your space and RAM free. Certain apps can also be transfered to the SD card using settings.
No Lag: There is certainly no lag on the screen when you are hopping from one app to another. The snapdragon 200 makes everything run smooth.
Corning Gorilla Glass 3: Yes, it is not only scratch proof but no messy thumprints also.....makes the screen more visible.
USB: It only works with a data cable and not an OTG

All in all, the Moto E is a seriously good handset that gives you just about everything you would need in a budget smartphone!"""

# Used when tokenizing words
sentence_re = r'''(?x)      # set flag to allow verbose regexps
      ([A-Z])(\.[A-Z])+\.?  # abbreviations, e.g. U.S.A.
    | \w+(-\w+)*            # words with optional internal hyphens
    | \$?\d+(\.\d+)?%?      # currency and percentages, e.g. $12.40, 82%
    | \.\.\.                # ellipsis
    | [][.,;"'?():-_`]      # these are separate tokens
'''

lemmatizer = nltk.WordNetLemmatizer()
stemmer = nltk.stem.porter.PorterStemmer()

#Taken from Su Nam Kim Paper...
grammar = r"""
    NBAR:
        {<NN.*|JJ>*<NN.*>}  # Nouns and Adjectives, terminated with Nouns
        
    NP:
        {<NBAR>}
        {<NBAR><IN><NBAR>}  # Above, connected with in/of/etc...
"""
chunker = nltk.RegexpParser(grammar)

toks = nltk.word_tokenize(text)
postoks = nltk.tag.pos_tag(toks)

print postoks

tree = chunker.parse(postoks)

from nltk.corpus import stopwords
stopwords = stopwords.words('english')


def leaves(tree):
    """Finds NP (nounphrase) leaf nodes of a chunk tree."""
    for subtree in tree.subtrees(filter = lambda t: t.label()=='NP'):
        yield subtree.leaves()

def normalise(word):
    """Normalises words to lowercase and stems and lemmatizes it."""
    word = word.lower()
    word = stemmer.stem_word(word)
    word = lemmatizer.lemmatize(word)
    return word

def acceptable_word(word):
    """Checks conditions for acceptable word: length, stopword."""
    accepted = bool(2 <= len(word) <= 40
        and word.lower() not in stopwords)
    return accepted


def get_terms(tree):
    for leaf in leaves(tree):
        term = [ normalise(w) for w,t in leaf if acceptable_word(w) ]
        yield term

terms = get_terms(tree)

for term in terms:
    for word in term:
        print word,
    print
