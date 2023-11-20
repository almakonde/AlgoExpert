def calculate_change_recursive(n, coins_values, result):
    if n <= 0 or not coins_values:
        return result
    
    coin_value = coins_values[0]
    coin_name = get_coin_name(coin_value)
    
    count = n // coin_value
    if count > 0:
        result[coin_name] = int(count)
        n -= coin_value * int(count)
    
    return calculate_change_recursive(n, coins_values[1:], result)

def get_coin_name(value):
    coins = {
        5: "5 рублей",
        2: "2 рубля",
        1: "1 рубль",
        50: "50 копеек",
        10: "10 копеек",
        5: "5 копеек",
        1: "1 копейка"
    }
    return coins.get(value)

def main():
    sum_to_return = int(float(input('Введите сумму сдачи в рублях: ') * 100))
    
    result = calculate_change_recursive(sum_to_return, [500, 200, 100, 50, 10, 5, 1], {})
    
    print('Для выдачи суммы сдачи потребуется:')
    
    for coin_name, count in result.items():
        print(f'{count} Монет(а) номиналом {coin_name}.')

if __name__ == "__main__":
    main()