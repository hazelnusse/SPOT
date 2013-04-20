#include "timestampednote.h"

TimeStampedNote::TimeStampedNote(int Time, const QString &Note)
    : Time_(Time), Note_(Note)
{

}

QString TimeStampedNote::toString(format_t f)
{
  QString result("");
  if (f == hms) {
    int hours = Time_ / (1000 * 60 * 60);
    int minutes = Time_ / (1000 * 60) - hours * 60;
    int seconds = Time_ / 1000 - minutes * 60;

    if (hours < 10)
      result += "0";
    result += QString::number(hours) + ":";

    if (minutes < 10)
      result += "0";
    result += QString::number(minutes) + ":";

    if (seconds < 10)
      result += "0";
    result += QString::number(seconds);
  } else {
    result += QString::number(Time_);
  }

  return result + ":" + Note_;
}
