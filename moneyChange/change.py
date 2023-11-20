def calculate_change_recursive(coins, amount, current_coins=None, min_coins=None):
    if current_coins is None:
        current_coins = {}
    if min_coins is None:
        min_coins = {'count': float('inf'), 'coins': {}}

    if amount == 0:
        if len(current_coins) < min_coins['count']:
            min_coins['count'] = len(current_coins)
            min_coins['coins'] = current_coins.copy()
        return

    valid_coins = [coin for coin in coins if coin <= amount]

    def process_coin(coin):
        remaining_amount = amount - coin
        remaining_change = current_coins.copy()
        remaining_change[coin] = remaining_change.get(coin, 0) + 1

        calculate_change_recursive(coins, remaining_amount, remaining_change, min_coins)

    list(map(process_coin, valid_coins))

    return min_coins['coins'] if min_coins['count'] != float('inf') else None

# Пример использования
coins_available = [1, 5, 10, 50, 100, 200, 500]
amount_to_return = int(input("Введите сумму сдачи в копейках: "))

result = calculate_change_recursive(coins_available, amount_to_return)

if result is not None:
    print("Минимальное количество монет для сдачи:")
    for coin, count in result.items():
        print(f"{coin} копеек: {count} шт.")
else:
    print("Невозможно выдать сдачу.")
