/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:19:27 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/22 15:41:23 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_string(char *str)
{
	if (!str)
		return (ft_putstr_fd("(null)", 1));
	return (ft_putstr_fd(str, 1));
}

int	ft_print_ptr(void *str)
{
	if (!str)
		return (ft_putstr_fd("(nil)", 1));
	write(1, "0x", 2);
	return (ft_putbase(*(size_t *)&str, "0123456789abcdef", 1) + 2);
}

int	ft_put_type(char type, va_list args)
{
	if (type == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (type == 's')
		return (ft_print_string(va_arg(args, char *)));
	else if (type == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else if (type == 'i' || type == 'd')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (type == 'u')
		return (ft_putnbr_fd(va_arg(args, unsigned int), 1));
	else if (type == 'x')
		return (ft_putbase(va_arg(args, unsigned int), "0123456789abcdef", 1));
	else if (type == 'X')
		return (ft_putbase(va_arg(args, unsigned int), "0123456789ABCDEF", 1));
	else if (type == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	char	type;
	int		output_len;

	output_len = 0;
	va_start(args, input);
	while (*input)
	{
		if (*input == '%' && *(input + 1))
		{
			input++;
			type = (char)(*input);
			output_len += ft_put_type(type, args);
			input++;
		}
		if (*input != '%' && *input)
		{
			write (1, &input[0], 1);
			output_len++;
			input++;
		}
	}
	va_end(args);
	return (output_len);
}

// int	main(void)
// {
// 	// const char	printme[]="testtest";
// 	// const char	input[]="c = %c\ns = %s\np = %p\nd = %d\ni = %i\n
// u = %u\nx = %x
// 	// \nX = %X\npercent = %%";
// 	// const char	input[]="p = %p";
// 	// ft_printf(input, 'a', printme, printme, 5, -1234567, 1234567, 1234567, 
// 	// 1234567);
// 	// printf(input, 'a', printme, printme, 5, -1234567, 1234567, 1234567, 
// 	// 1234567);
// 	// printf("\nabc%pefe\n", (void *)0);
// 	// printf("\n%d", printf(input, 1234567));
// 	// ft_printf(" NULL %s NULL ", (char *)NULL);
// 	// write(1, "\n", 1);
// 	// printf(" NULL %s NULL ", (char *)NULL);
// 	// ft_printf(" %p %p ", 0, 0);
// 	// write(1, "\n", 1);
// 	// printf(" %p %p ", (void *)0, (void *)0);
// 	return (0);
// }