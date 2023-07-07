import jax.numpy as np
from jax.scipy.stats import norm
from jax import grad


class EuropeanCall:

    def call_price(
        self, asset_price, asset_volatility, strike_price,
        time_to_expiration, risk_free_rate
            ):
        b = np.exp(-risk_free_rate*time_to_expiration).astype('float')
        x1 = np.log(asset_price/(b*strike_price))
        x1 += (.5*(asset_volatility*asset_volatility)*time_to_expiration)
        x1 = x1/(asset_volatility*(time_to_expiration**.5))
        z1 = norm.cdf(x1)
        z1 = z1*asset_price
        x2 = np.log(asset_price/(b*strike_price)) - .5*(asset_volatility*asset_volatility)*time_to_expiration
        x2 = x2/(asset_volatility*(time_to_expiration**.5))
        z2 = norm.cdf(x2)
        z2 = b*strike_price*z2
        return z1 - z2

    def __init__(
        self, inputs
            ):
        self.asset_price = inputs[0]
        self.asset_volatility = inputs[1]
        self.strike_price = inputs[2]
        self.time_to_expiration = inputs[3]
        self.risk_free_rate = inputs[4]
        self.price = self.call_price(self.asset_price, self.asset_volatility, self.strike_price, self.time_to_expiration, self.risk_free_rate)

        self.gradient_func = grad(self.call_price, (0, 1, 3, 4))
        self.delta, self.vega, self.theta, self.rho = self.gradient_func(inputs[0], inputs[1], inputs[2], inputs[3], inputs[4])
        self.theta /= -365
        self.vega /= 100
        self.rho /= 100


class EuropeanPut:

    def put_price(
        self, asset_price, asset_volatility, strike_price,
        time_to_expiration, risk_free_rate
            ):
        b = np.exp(-risk_free_rate*time_to_expiration)
        x1 = np.log((b*strike_price)/asset_price) + .5*(asset_volatility*asset_volatility)*time_to_expiration
        x1 = x1/(asset_volatility*(time_to_expiration**.5))
        z1 = norm.cdf(x1)
        z1 = b*strike_price*z1
        x2 = np.log((b*strike_price)/asset_price) - .5*(asset_volatility*asset_volatility)*time_to_expiration
        x2 = x2/(asset_volatility*(time_to_expiration**.5))
        z2 = norm.cdf(x2)
        z2 = asset_price*z2
        return z1 - z2

    def __init__(
        self, inputs
            ):
        self.asset_price = inputs[0]
        self.asset_volatility = inputs[1]
        self.strike_price = inputs[2]
        self.time_to_expiration = inputs[3]
        self.risk_free_rate = inputs[4]
        self.price = self.call_price(self.asset_price, self.asset_volatility, self.strike_price, self.time_to_expiration, self.risk_free_rate)

        self.gradient_func = grad(self.put_price, (0, 1, 3, 4))
        self.delta, self.vega, self.theta, self.rho = self.gradient_func(inputs[0], inputs[1], inputs[2], inputs[3], inputs[4])
        self.theta /= -365
        self.vega /= 100
        self.rho /= 100


inputs = np.array([3109.62, .2102, 3060.0, 27/365, .017])
ec = EuropeanCall(inputs.astype('float'))
print(ec.delta, ec.vega, ec.theta, ec.rho)
