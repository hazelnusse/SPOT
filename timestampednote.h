#ifndef TIMESTAMPEDNOTE_H
#define TIMESTAMPEDNOTE_H
#include <QString>

class TimeStampedNote
{
public:
  enum format_t {hms, ms};
  TimeStampedNote(int Time, const QString &Note);
  QString toString(format_t f = hms);
private:
    int Time_;
    QString Note_;
};

#endif // TIMESTAMPEDNOTE_H
