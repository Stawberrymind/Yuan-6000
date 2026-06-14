#include <TFT_eSPI.h>
#include <Encoder.h>
#include <qrcode.h>
#define ENC_A 1
#define ENC_B 2
#define BTN_UP 4
#define BTN_DOWN 5
#define BTN_LEFT 6
#define BTN_RIGHT 7
#define BTN_CENTER 8

TFT_eSPI tft = TFT_eSPI();
Encoder encoder(ENC_A, ENC_B);

constexpr float RATE_INR = 14.04f;
constexpr float RATE_USD = 0.15f;
constexpr float RATE_EUR = 0.13f;

const char *WECHAT_QR_TEXT =
    "urwechatqr";

enum class Screen
{
    Splash,
    Converter,
    QR
};

enum class Currency
{
    INR,
    USD,
    EUR
};

struct AppState
{
    Screen screen = Screen::Splash;

    Currency currency = Currency::INR;

    int yuanTarget = 100;
    float yuanDisplayed = 100.0f;

    bool redraw = true;
};

AppState app;

struct Button
{
    bool current = false;
    bool previous = false;
    uint32_t pressTime = 0;
};

Button centerButton;

uint32_t lastFrame = 0;
const uint32_t FRAME_TIME_MS = 16;

String currencyName()
{
    switch (app.currency)
    {
    case Currency::INR:
        return "INR";

    case Currency::USD:
        return "USD";

    case Currency::EUR:
        return "EUR";
    }

    return "";
}

String currencySymbol()
{
    switch (app.currency)
    {
    case Currency::INR:
        return "₹";

    case Currency::USD:
        return "$";

    case Currency::EUR:
        return "€";
    }

    return "";
}

float conversionRate()
{
    switch (app.currency)
    {
    case Currency::INR:
        return RATE_INR;

    case Currency::USD:
        return RATE_USD;

    case Currency::EUR:
        return RATE_EUR;
    }

    return 0.0f;
}

float convertedValue()
{
    return app.yuanDisplayed * conversionRate();
}

bool pressed(uint8_t pin)
{
    return !digitalRead(pin);
}

void setup()
{
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);
    pinMode(BTN_CENTER, INPUT_PULLUP);

    tft.init();
    tft.setRotation(0);

    tft.fillScreen(TFT_BLACK);

    app.screen = Screen::Splash;
}

void clearCenterArea()
{
    tft.fillRoundRect(
        20,
        40,
        200,
        140,
        12,
        TFT_BLACK);
}

void drawSplash()
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextDatum(MC_DATUM);

    for (int i = 0; i < 255; i += 15)
    {
        uint16_t color = tft.color565(i, i, 0);

        tft.fillScreen(TFT_BLACK);

        tft.setTextColor(color);

        tft.setTextSize(5);
        tft.drawString("Y", 120, 80);

        tft.setTextSize(2);
        tft.drawString(
            "Yuan Converter 6000",
            120,
            150);

        delay(40);
    }

    delay(500);

    app.screen = Screen::Converter;
    app.redraw = true;
}

void drawCurrencyTabs()
{
    tft.setTextDatum(MC_DATUM);

    uint16_t inrColor = TFT_DARKGREY;
    uint16_t usdColor = TFT_DARKGREY;
    uint16_t eurColor = TFT_DARKGREY;

    switch (app.currency)
    {
    case Currency::INR:
        inrColor = TFT_GREEN;
        break;

    case Currency::USD:
        usdColor = TFT_GREEN;
        break;

    case Currency::EUR:
        eurColor = TFT_GREEN;
        break;
    }

    tft.fillRect(0, 200, 240, 40, TFT_BLACK);

    tft.setTextColor(inrColor);
    tft.drawString("INR", 60, 220);

    tft.setTextColor(usdColor);
    tft.drawString("USD", 120, 220);

    tft.setTextColor(eurColor);
    tft.drawString("EUR", 180, 220);
}

void drawConverterScreen()
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextDatum(MC_DATUM);

    tft.setTextColor(TFT_CYAN);
    tft.setTextSize(2);

    tft.drawString(
        "CNY -> " + currencyName(),
        120,
        20);

    drawCurrencyTabs();
}

void drawConverterValues()
{
    clearCenterArea();

    tft.setTextDatum(MC_DATUM);

    tft.setTextColor(TFT_YELLOW);

    tft.setTextSize(4);

    tft.drawString(
        "Y" + String((int)app.yuanDisplayed),
        120,
        85);

    float value = convertedValue();

    tft.setTextColor(TFT_GREEN);

    tft.setTextSize(3);

    tft.drawString(
        currencySymbol() + String(value, 2),
        120,
        145);
}

void drawQRCode()
{
    tft.fillScreen(TFT_WHITE);

    tft.setTextDatum(MC_DATUM);

    QRCode qrcode;

    uint8_t qrcodeData[qrcode_getBufferSize(5)];

    qrcode_initText(
        &qrcode,
        qrcodeData,
        5,
        ECC_LOW,
        WECHAT_QR_TEXT);

    const int scale = 6;

    int offsetX =
        (240 - qrcode.size * scale) / 2;

    int offsetY =
        (240 - qrcode.size * scale) / 2;

    for (int y = 0; y < qrcode.size; y++)
    {
        for (int x = 0; x < qrcode.size; x++)
        {
            if (qrcode_getModule(
                    &qrcode,
                    x,
                    y))
            {
                tft.fillRect(
                    offsetX + x * scale,
                    offsetY + y * scale,
                    scale,
                    scale,
                    TFT_BLACK);
            }
        }
    }

    tft.setTextColor(TFT_BLACK);

    tft.setTextSize(1);

    tft.drawString(
        "Press center to return",
        120,
        225);
}

void updateAnimations()
{
    app.yuanDisplayed +=
        (app.yuanTarget -
         app.yuanDisplayed) *
        0.18f;

    if (fabs(
            app.yuanTarget -
            app.yuanDisplayed) < 0.05f)
    {
        app.yuanDisplayed =
            app.yuanTarget;
    }
}

void nextCurrency()
{
    switch (app.currency)
    {
    case Currency::INR:
        app.currency = Currency::USD;
        break;

    case Currency::USD:
        app.currency = Currency::EUR;
        break;

    case Currency::EUR:
        app.currency = Currency::INR;
        break;
    }

    app.redraw = true;
}

void previousCurrency()
{
    switch (app.currency)
    {
    case Currency::INR:
        app.currency = Currency::EUR;
        break;

    case Currency::USD:
        app.currency = Currency::INR;
        break;

    case Currency::EUR:
        app.currency = Currency::USD;
        break;
    }

    app.redraw = true;
}

long lastEncoderPosition = 0;
uint32_t lastEncoderMove = 0;

void handleEncoder()
{
    long currentPos =
        encoder.read() / 4;

    long delta =
        currentPos -
        lastEncoderPosition;

    if (delta == 0)
        return;

    uint32_t now = millis();

    uint32_t speed =
        now - lastEncoderMove;

    lastEncoderMove = now;

    int step = 1;

    //
    // Encoder acceleration
    //

    if (speed < 15)
    {
        step = 50;
    }
    else if (speed < 40)
    {
        step = 10;
    }
    else
    {
        step = 1;
    }

    app.yuanTarget +=
        delta * step;

    if (app.yuanTarget < 0)
    {
        app.yuanTarget = 0;
    }

    if (app.yuanTarget > 999999)
    {
        app.yuanTarget = 999999;
    }

    lastEncoderPosition =
        currentPos;
}

bool leftPrev = false;
bool rightPrev = false;

void handleCurrencyButtons()
{
    bool left =
        pressed(BTN_LEFT);

    bool right =
        pressed(BTN_RIGHT);

    if (left && !leftPrev)
    {
        previousCurrency();
    }

    if (right && !rightPrev)
    {
        nextCurrency();
    }

    leftPrev = left;
    rightPrev = right;
}

bool centerHeld = false;
bool qrOpenedByHold = false;

const uint32_t LONG_PRESS_MS = 800;

void handleCenterButton()
{
    bool state =
        pressed(BTN_CENTER);

    if (state &&
        !centerButton.previous)
    {
        centerButton.pressTime =
            millis();

        qrOpenedByHold = false;
    }

    if (state)
    {
        uint32_t held =
            millis() -
            centerButton.pressTime;

        if (
            held > LONG_PRESS_MS &&
            !qrOpenedByHold)
        {
            qrOpenedByHold = true;

            if (app.screen ==
                Screen::Converter)
            {
                app.screen =
                    Screen::QR;

                drawQRCode();
            }
        }
    }

    if (
        !state &&
        centerButton.previous)
    {

        if (
            app.screen ==
            Screen::QR)
        {
            app.screen =
                Screen::Converter;

            app.redraw = true;
        }
    }

    centerButton.previous =
        state;
}

void render()
{
    if (app.screen ==
        Screen::Converter)
    {
        if (app.redraw)
        {
            drawConverterScreen();

            app.redraw = false;
        }

        drawConverterValues();
    }
}

void update()
{
    handleEncoder();

    handleCurrencyButtons();

    handleCenterButton();

    updateAnimations();
}

void loop()
{

    static bool splashDone =
        false;

    if (!splashDone)
    {
        drawSplash();

        splashDone = true;
    }

    uint32_t now =
        millis();

    if (
        now - lastFrame <
        FRAME_TIME_MS)
    {
        return;
    }

    lastFrame = now;

    update();

    render();
}