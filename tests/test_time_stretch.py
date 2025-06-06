#! /usr/bin/env python
#
# Copyright 2024 Spotify AB
#
# Licensed under the GNU Public License, Version 3.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    https://www.gnu.org/licenses/gpl-3.0.html
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


import numpy as np
import pytest

from pedalboard import time_stretch


@pytest.mark.parametrize("semitones", [-1, 0, 1])
@pytest.mark.parametrize("stretch_factor", [0.1, 0.75, 1, 1.25])
@pytest.mark.parametrize("fundamental_hz", [440])
@pytest.mark.parametrize("sample_rate", [22050, 44100, 48000])
@pytest.mark.parametrize("high_quality", [True, False])
def test_time_stretch(semitones, stretch_factor, fundamental_hz, sample_rate, high_quality):
    num_seconds = 1.0
    samples = np.arange(num_seconds * sample_rate)
    sine_wave = np.sin(2 * np.pi * fundamental_hz * samples / sample_rate).astype(np.float32)

    output = time_stretch(
        sine_wave,
        sample_rate,
        stretch_factor=stretch_factor,
        pitch_shift_in_semitones=semitones,
        high_quality=high_quality,
    )

    assert np.all(np.isfinite(output))
    assert output.shape[1] == int((num_seconds * sample_rate) / stretch_factor)
    if stretch_factor != 1 or semitones != 0:
        min_samples = min(output.shape[1], sine_wave.shape[0])
        assert not np.allclose(output[:, :min_samples], sine_wave[:min_samples])


@pytest.mark.parametrize("high_quality", [True, False])
@pytest.mark.parametrize("transient_mode", ["crisp", "mixed", "smooth"])
@pytest.mark.parametrize("transient_detector", ["compound", "percussive", "soft"])
@pytest.mark.parametrize("retain_phase_continuity", [True, False])
@pytest.mark.parametrize("use_long_fft_window", [None, True, False])
@pytest.mark.parametrize("use_time_domain_smoothing", [True, False])
@pytest.mark.parametrize("preserve_formants", [True, False])
def test_time_stretch_extra_options(
    high_quality,
    transient_mode,
    transient_detector,
    retain_phase_continuity,
    use_long_fft_window,
    use_time_domain_smoothing,
    preserve_formants,
):
    sample_rate = 22050
    num_seconds = 0.5
    fundamental_hz = 440
    samples = np.arange(num_seconds * sample_rate)
    sine_wave = np.sin(2 * np.pi * fundamental_hz * samples / sample_rate).astype(np.float32)

    output = time_stretch(
        sine_wave,
        sample_rate,
        stretch_factor=1.5,
        pitch_shift_in_semitones=1,
        high_quality=high_quality,
        transient_mode=transient_mode,
        transient_detector=transient_detector,
        retain_phase_continuity=retain_phase_continuity,
        use_long_fft_window=use_long_fft_window,
        use_time_domain_smoothing=use_time_domain_smoothing,
        preserve_formants=preserve_formants,
    )

    assert np.all(np.isfinite(output))


@pytest.mark.parametrize("semitones", [0])
@pytest.mark.parametrize("stretch_factor", [1.0])
@pytest.mark.parametrize("fundamental_hz", [440, 220, 110])
@pytest.mark.parametrize("sample_rate", [22050, 44100])
@pytest.mark.parametrize("high_quality", [True, False])
def test_time_stretch_long_passthrough(
    semitones, stretch_factor, fundamental_hz, sample_rate, high_quality
):
    num_seconds = 30.0
    samples = np.arange(num_seconds * sample_rate)
    sine_wave = np.sin(2 * np.pi * fundamental_hz * samples / sample_rate).astype(np.float32)

    output = time_stretch(
        sine_wave,
        sample_rate,
        stretch_factor=stretch_factor,
        pitch_shift_in_semitones=semitones,
        high_quality=high_quality,
    )
    np.testing.assert_allclose(output[0], sine_wave, atol=0.25)


def test_time_stretch_does_not_segfault():
    # https://github.com/spotify/pedalboard/issues/340
    sr = 44100
    x = np.random.default_rng().uniform(size=sr * 10).astype(np.float32)
    time_stretch(x, sr, high_quality=False, use_time_domain_smoothing=True)


@pytest.mark.parametrize("semitones_start", [-1, 0, 1])
@pytest.mark.parametrize("semitones_end", [-1, 0, 1])
@pytest.mark.parametrize("stretch_factor_start", [0.75, 1, 1.25])
@pytest.mark.parametrize("stretch_factor_end", [0.75, 1, 1.25])
def test_time_stretch_with_array(
    semitones_start, semitones_end, stretch_factor_start, stretch_factor_end
):
    sample_rate = 44100
    fundamental_hz = 440
    num_seconds = 1.0
    samples = np.arange(num_seconds * sample_rate)
    sine_wave = np.sin(2 * np.pi * fundamental_hz * samples / sample_rate).astype(np.float32)

    output = time_stretch(
        sine_wave,
        sample_rate,
        stretch_factor=np.linspace(stretch_factor_start, stretch_factor_end, sine_wave.shape[0]),
        pitch_shift_in_semitones=np.linspace(semitones_start, semitones_end, sine_wave.shape[0]),
    )

    assert np.all(np.isfinite(output))


def test_time_stretch_mismatched_buffer_length_and_stretch_factors():
    with pytest.raises(ValueError):
        time_stretch(
            np.zeros((1, 10), dtype=np.float32),
            44100,
            stretch_factor=np.linspace(0.1, 1.0, 11).astype(np.float64),
        )


def test_time_stretch_mismatched_buffer_length_and_pitch_shift():
    with pytest.raises(ValueError) as e:
        time_stretch(
            np.zeros((1, 10), dtype=np.float32),
            44100,
            pitch_shift_in_semitones=np.linspace(0.1, 1.0, 11).astype(np.float64),
        )
    assert "buffer" in str(e)


def test_time_stretch_variable_stretch_factor_out_of_range():
    with pytest.raises(ValueError) as e:
        time_stretch(
            np.zeros((1, 10), dtype=np.float32),
            44100,
            stretch_factor=np.zeros((10,), dtype=np.float64),
        )
    assert "element at index 0 was 0" in str(e)


def test_time_stretch_variable_pitch_shift_out_of_range():
    with pytest.raises(ValueError) as e:
        time_stretch(
            np.zeros((1, 10), dtype=np.float32),
            44100,
            pitch_shift_in_semitones=np.ones((10,), dtype=np.float64) * 73,
        )
    assert "element at index 0 was 73" in str(e)
