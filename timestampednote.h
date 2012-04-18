#ifndef TIMESTAMPEDNOTE_H
#define TIMESTAMPEDNOTE_H
#include <QString>

class TimeStampedNote
{
public:
    TimeStampedNote(const QString &Time, const QString &Note);
    QString toString() {return Time_ + ": " + Note_;}
private:
    QString Time_;
    QString Note_;
};

#endif // TIMESTAMPEDNOTE_H
