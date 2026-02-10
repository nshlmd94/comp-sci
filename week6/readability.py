def main():
    userInput = input("Enter the text: ")
    letters, words, sentences = count(userInput)
    index = calculate(letters, words, sentences)
    
    if index < 1:
        print(f"Before Grade 1")
    elif index > 16:
        print(f"Grade 16+")
    else:
        print(f"Grade {round(index)}")

def count(text):
    letters = 0
    words = 1
    sentences = 0

    for i in text:
        if i.isalpha() == True:
            letters += 1
        elif i in [" "]:
            words += 1
        elif i in ["!", ".", "?"]:
            sentences += 1
        else:
            continue
    
    return letters, words, sentences

def calculate(letters, words, sentences):
    return 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8

if __name__ == "__main__":
    main()
            


