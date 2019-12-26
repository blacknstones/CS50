from cs50 import get_float

def main():
    while True:
        dollar = get_float("Change owed: ")
        cents = round(dollar * 100)
        if dollar > 0:
            break

    quarters = cents // 25
    dimes = (cents % 25) // 10
    nickels = ((cents % 25) % 10) // 5
    pennies = ((cents % 25) % 10) % 5

    counter = quarters + dimes + nickels + pennies

    print(counter)

if __name__ == "__main__":
    main()