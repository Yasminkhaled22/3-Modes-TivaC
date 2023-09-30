#ifndef Bitwise
#define Bitwise

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Read a certain bit in any register */
#define GET_BIT(REG,BIT) ( ( REG & (1<<BIT) ) >> BIT)
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

#endif
